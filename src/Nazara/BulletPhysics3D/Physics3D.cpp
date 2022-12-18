// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - BulletPhysics3D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/BulletPhysics3D/Physics3D.hpp>
#include <Nazara/BulletPhysics3D/Debug.hpp>

namespace Nz
{
	Physics3D::Physics3D(Config /*config*/) :
	ModuleBase("Physics3D", this)
	{
	}

	Physics3D* Physics3D::s_instance;
}
