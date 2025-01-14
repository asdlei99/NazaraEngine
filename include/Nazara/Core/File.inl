// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Core module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Core/Algorithm.hpp>
#include <Nazara/Core/Debug.hpp>

namespace Nz
{
	/*!
	* \brief Computes the hash for the file
	* \return ByteArray represing the result of the hash of the file
	*
	* \param hash Hash to execute
	* \param filePath Path for the file
	*/

	inline ByteArray File::ComputeHash(HashType hash, const std::filesystem::path& filePath)
	{
		return ComputeHash(*AbstractHash::Get(hash), filePath);
	}

	/*!
	* \brief Computes the hash for the file
	* \return ByteArray represing the result of the hash of the file
	*
	* \param hash Hash to execute
	* \param filePath Path for the file
	*/

	inline ByteArray File::ComputeHash(AbstractHash& hash, const std::filesystem::path& filePath)
	{
		return Nz::ComputeHash(hash, File(filePath));
	}

	inline bool File::CheckFileOpening()
	{
		if (m_openMode.Test(OpenMode::Defer))
		{
			if (!Open(m_filePath, m_openMode & ~OpenMode::Defer))
			{
				NazaraError("failed to open file");
				return false;
			}
		}

		return true;
	}
}

#include <Nazara/Core/DebugOff.hpp>
