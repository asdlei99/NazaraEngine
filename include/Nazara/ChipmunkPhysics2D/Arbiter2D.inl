// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - ChipmunkPhysics2D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/ChipmunkPhysics2D/Arbiter2D.hpp>
#include <memory>
#include <Nazara/ChipmunkPhysics2D/Debug.hpp>

namespace Nz
{
	inline Arbiter2D::Arbiter2D(cpArbiter* arbiter) :
	m_arbiter(arbiter)
	{
	}
}

#include <Nazara/ChipmunkPhysics2D/DebugOff.hpp>
