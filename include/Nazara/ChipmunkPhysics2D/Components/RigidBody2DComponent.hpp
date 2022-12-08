// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - ChipmunkPhysics2D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CHIPMUNKPHYSICS2D_COMPONENTS_RIGIDBODY2DCOMPONENT_HPP
#define NAZARA_CHIPMUNKPHYSICS2D_COMPONENTS_RIGIDBODY2DCOMPONENT_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/ChipmunkPhysics2D/RigidBody2D.hpp>

namespace Nz
{
	class NAZARA_CHIPMUNKPHYSICS2D_API RigidBody2DComponent : public RigidBody2D
	{
		friend class Physics2DSystem;

		public:
			using RigidBody2D::RigidBody2D;
			RigidBody2DComponent(const RigidBody2DComponent&) = default;
			RigidBody2DComponent(RigidBody2DComponent&&) noexcept = default;
			~RigidBody2DComponent() = default;

			RigidBody2DComponent& operator=(const RigidBody2DComponent&) = default;
			RigidBody2DComponent& operator=(RigidBody2DComponent&&) noexcept = default;
	};
}

#include <Nazara/ChipmunkPhysics2D/Components/RigidBody2DComponent.inl>

#endif // NAZARA_CHIPMUNKPHYSICS2D_COMPONENTS_RIGIDBODY2DCOMPONENT_HPP
