// Copyright (C) 2015 Jérôme Leclercq
// This file is part of the "Nazara Engine - Utility module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Network/TcpClient.hpp>
#include <Nazara/Core/CallOnExit.hpp>
#include <Nazara/Core/Error.hpp>
#include <limits>
#include <Nazara/Network/Debug.hpp>

#if defined(NAZARA_PLATFORM_WINDOWS)
#include <Nazara/Network/Win32/SocketImpl.hpp>
#else
#error Missing implementation: Socket
#endif

namespace Nz
{
	SocketState TcpClient::Connect(const IpAddress& remoteAddress)
	{
		NazaraAssert(remoteAddress.IsValid(), "Invalid remote address");
		NazaraAssert(remoteAddress.GetPort() != 0, "Remote address has no port");

		Open(remoteAddress.GetProtocol());

		CallOnExit restoreBlocking;
		if (m_isBlockingEnabled)
		{
			SocketImpl::SetBlocking(m_handle, false);
			restoreBlocking.Reset([this] ()
			{
				SocketImpl::SetBlocking(m_handle, true);
			});
		}

		SocketState state = SocketImpl::Connect(m_handle, remoteAddress, &m_lastError);
		m_peerAddress = (state != SocketState_NotConnected) ? remoteAddress : IpAddress::Invalid;

		UpdateState(state);
		return state;
	}

	SocketState TcpClient::Connect(const String& hostName, NetProtocol protocol, const String& service, ResolveError* error)
	{
		Disconnect();

		UpdateState(SocketState_Resolving);
		std::vector<HostnameInfo> results = IpAddress::ResolveHostname(protocol, hostName, service, error);
		if (results.empty())
		{
			m_lastError = SocketError_ResolveError;

			UpdateState(SocketState_NotConnected);
			return m_state;
		}

		IpAddress hostnameAddress;
		for (const HostnameInfo& result : results)
		{
			//TODO: Check PF_ type (TCP)
			if (!result.address)
				continue;

			hostnameAddress = result.address;
			break; //< Take first valid address
		}

		return Connect(hostnameAddress);
	}

	void TcpClient::EnableLowDelay(bool lowDelay)
	{
		NazaraAssert(m_handle != SocketImpl::InvalidHandle, "Invalid handle");

		if (m_isLowDelayEnabled != lowDelay)
		{
			SocketImpl::SetNoDelay(m_handle, lowDelay, &m_lastError);
			m_isLowDelayEnabled = lowDelay;
		}
	}

	void TcpClient::EnableKeepAlive(bool keepAlive, UInt64 msTime, UInt64 msInterval)
	{
		NazaraAssert(m_handle != SocketImpl::InvalidHandle, "Invalid handle");

		if (m_isKeepAliveEnabled != keepAlive || m_keepAliveTime != msTime || m_keepAliveInterval != msInterval)
		{
			SocketImpl::SetKeepAlive(m_handle, keepAlive, msTime, msInterval, &m_lastError);
			m_isKeepAliveEnabled = keepAlive;
			m_keepAliveInterval = msInterval;
			m_keepAliveTime = msTime;
		}
	}

	SocketState TcpClient::QueryState()
	{
		// Check our state depending on our last state
		switch (m_state)
		{
			case SocketState_Connecting:
			{
				// If we were connecting, check how it's going
				SocketError getError;
				SocketError error = SocketImpl::GetLastError(m_handle, &getError);

				if (getError != SocketError_NoError)
					break; //< Do not update state if we cannot get socket state

				if (error == SocketError_NoError)
				{
					// No error yet, we're still connecting or connected, check that by calling Connect again
					return Connect(m_peerAddress);
				}
				else
				{
					// Our connection attempt failed
					m_lastError = error;
					UpdateState(SocketState_NotConnected);
				}

				break;
			}

			default:
			{
				// Check our peer address, if it works we're connected
				SocketError error;
				m_peerAddress = SocketImpl::QueryPeerAddress(m_handle, &error);
				if (m_peerAddress == IpAddress::Invalid)
				{
					// Other errors mean a problem while getting the peer address
					if (error == SocketError_ConnectionClosed)
						UpdateState(SocketState_NotConnected);
				}
				else
					UpdateState(SocketState_Connected); // If we are not connecting and have a peer address, we are connected

				break;
			}
		}

		return m_state;
	}

	bool TcpClient::Receive(void* buffer, std::size_t size, std::size_t* received)
	{
		NazaraAssert(m_handle != SocketImpl::InvalidHandle, "Invalid handle");
		NazaraAssert(buffer && size > 0, "Invalid buffer");

		int read;
		if (!SocketImpl::Receive(m_handle, buffer, static_cast<int>(size), &read, &m_lastError))
		{
			switch (m_lastError)
			{
				case SocketError_ConnectionClosed:
				case SocketError_ConnectionRefused:
					UpdateState(SocketState_NotConnected);
					break;

				default:
					break;
			}

			return false;
		}

		if (received)
			*received = read;

		UpdateState(SocketState_Connected);
		return true;
	}

	bool TcpClient::Send(const void* buffer, std::size_t size, std::size_t* sent)
	{
		NazaraAssert(m_handle != SocketImpl::InvalidHandle, "Invalid handle");
		NazaraAssert(buffer && size > 0, "Invalid buffer");

		CallOnExit updateSent;
		std::size_t totalByteSent = 0;
		if (sent)
		{
			updateSent.Reset([sent, &totalByteSent] ()
			{
				*sent = totalByteSent;
			});
		}

		while (totalByteSent < size)
		{
			int sendSize = static_cast<int>(std::min<std::size_t>(size - totalByteSent, std::numeric_limits<int>::max())); //< Handle very large send
			int sentSize;
			if (!SocketImpl::Send(m_handle, reinterpret_cast<const UInt8*>(buffer) + totalByteSent, sendSize, &sentSize, &m_lastError))
			{
				switch (m_lastError)
				{
					case SocketError_ConnectionClosed:
					case SocketError_ConnectionRefused:
						UpdateState(SocketState_NotConnected);
						break;

					default:
						break;
				}

				return false;
			}

			totalByteSent += sentSize;
		}

		UpdateState(SocketState_Connected);
		return true;
	}

	bool TcpClient::WaitForConnected(UInt64 msTimeout)
	{
		switch (m_state)
		{
			case SocketState_Connected:
				return true;

			case SocketState_Connecting:
			{
				NazaraAssert(m_handle != SocketImpl::InvalidHandle, "Invalid handle");

				CallOnExit restoreBlocking;
				if (m_isBlockingEnabled)
				{
					SocketImpl::SetBlocking(m_handle, false);
					restoreBlocking.Reset([this] ()
					{
						SocketImpl::SetBlocking(m_handle, true);
					});
				}

				SocketState newState = SocketImpl::Connect(m_handle, m_peerAddress, msTimeout, &m_lastError);
				NazaraAssert(newState != SocketState_Connecting, "Invalid internal return");

				// Prevent valid peer address in non-connected state
				if (newState == SocketState_NotConnected)
					m_peerAddress = IpAddress::Invalid;

				UpdateState(newState);
				return newState == SocketState_Connected;
			}

			case SocketState_NotConnected:
				return false;
		}

		NazaraInternalError("Unhandled socket state (0x" + String::Number(m_state, 16) + ')');
		return false;
	}

	void TcpClient::OnClose()
	{
		AbstractSocket::OnClose();

		m_peerAddress = IpAddress::Invalid;
	}

	void TcpClient::OnOpened()
	{
		AbstractSocket::OnOpened();

		m_isLowDelayEnabled = false;  //< Nagle's algorithm, is this enabled everywhere?
		m_isKeepAliveEnabled = false; //< default documentation value, OS can change this (TODO: Query OS default value)
		m_keepAliveInterval = 1000;   //< default documentation value, OS can change this (TODO: Query OS default value)
		m_keepAliveTime = 7200000;    //< default documentation value, OS can change this (TODO: Query OS default value)
		m_peerAddress = IpAddress::Invalid;
	}

	void TcpClient::Reset(SocketHandle handle, const IpAddress& peerAddress)
	{
		Open(handle);
		m_peerAddress = peerAddress;
		UpdateState(SocketState_Connected);
	}
}