// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - JoltPhysics3D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/JoltPhysics3D/Debug.hpp>

namespace Nz
{
	inline void JoltCharacter::DisableSleeping()
	{
		return EnableSleeping(false);
	}

	inline UInt32 JoltCharacter::GetBodyIndex() const
	{
		return m_bodyIndex;
	}

	inline void JoltCharacter::SetImpl(std::shared_ptr<JoltCharacterImpl> characterImpl)
	{
		m_impl = std::move(characterImpl);
	}
}

#include <Nazara/JoltPhysics3D/DebugOff.hpp>
