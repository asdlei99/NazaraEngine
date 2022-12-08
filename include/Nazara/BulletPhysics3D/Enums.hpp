// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - BulletPhysics3D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_BULLETPHYSICS3D_ENUMS_HPP
#define NAZARA_BULLETPHYSICS3D_ENUMS_HPP

namespace Nz
{
	enum class ColliderType3D
	{
		Box,
		Capsule,
		Cone,
		Compound,
		ConvexHull,
		Cylinder,
		Heightfield,
		Null,
		Scene,
		Sphere,
		Tree,

		Max = Tree
	};
}

#endif // NAZARA_BULLETPHYSICS3D_ENUMS_HPP
