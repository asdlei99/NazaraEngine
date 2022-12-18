// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - BulletPhysics3D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_BULLETPHYSICS3D_PHYSWORLD3D_HPP
#define NAZARA_BULLETPHYSICS3D_PHYSWORLD3D_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/BulletPhysics3D/Config.hpp>
#include <Nazara/Math/Box.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/Utils/MovablePtr.hpp>
#include <string>
#include <unordered_map>

class btDynamicsWorld;

namespace Nz
{
	class RigidBody3D;

	class NAZARA_BULLETPHYSICS3D_API PhysWorld3D
	{
		public:
			PhysWorld3D();
			PhysWorld3D(const PhysWorld3D&) = delete;
			PhysWorld3D(PhysWorld3D&& ph) noexcept;
			~PhysWorld3D();

			btDynamicsWorld* GetDynamicsWorld();
			Vector3f GetGravity() const;
			std::size_t GetMaxStepCount() const;
			float GetStepSize() const;

			void SetGravity(const Vector3f& gravity);
			void SetMaxStepCount(std::size_t maxStepCount);
			void SetStepSize(float stepSize);

			void Step(float timestep);

			PhysWorld3D& operator=(const PhysWorld3D&) = delete;
			PhysWorld3D& operator=(PhysWorld3D&&) noexcept;

		private:
			struct BulletWorld;

			std::size_t m_maxStepCount;
			std::unique_ptr<BulletWorld> m_world;
			Vector3f m_gravity;
			float m_stepSize;
			float m_timestepAccumulator;
	};
}

#endif // NAZARA_BULLETPHYSICS3D_PHYSWORLD3D_HPP
