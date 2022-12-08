// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - BulletPhysics3D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_BULLETPHYSICS3D_PHYSWORLD3D_HPP
#define NAZARA_BULLETPHYSICS3D_PHYSWORLD3D_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/Math/Box.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/NewtonPhysics3D/Config.hpp>
#include <Nazara/Utils/MovablePtr.hpp>
#include <string>
#include <unordered_map>

class NewtonBody;
class NewtonJoint;
class NewtonMaterial;
class NewtonWorld;

namespace Nz
{
	class RigidBody3D;

	class NAZARA_NEWTONPHYSICS3D_API PhysWorld3D
	{
		public:
			using BodyIterator = std::function<bool(RigidBody3D& body)>;
			using AABBOverlapCallback = std::function<bool(const RigidBody3D& firstBody, const RigidBody3D& secondBody)>;
			using CollisionCallback = std::function<bool(const RigidBody3D& firstBody, const RigidBody3D& secondBody)>;

			PhysWorld3D();
			PhysWorld3D(const PhysWorld3D&) = delete;
			PhysWorld3D(PhysWorld3D&& ph) noexcept;
			~PhysWorld3D();

			void ForEachBodyInAABB(const Boxf& box, const BodyIterator& iterator);

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
			struct Callback
			{
				AABBOverlapCallback aabbOverlapCallback;
				CollisionCallback collisionCallback;
			};

			struct BulletWorld;

			std::unordered_map<Nz::UInt64, std::unique_ptr<Callback>> m_callbacks;
			std::unordered_map<std::string, int> m_materialIds;
			std::size_t m_maxStepCount;
			std::unique_ptr<BulletWorld> m_world;
			Vector3f m_gravity;
			float m_stepSize;
			float m_timestepAccumulator;
	};
}

#endif // NAZARA_BULLETPHYSICS3D_PHYSWORLD3D_HPP
