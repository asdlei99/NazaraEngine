// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - BulletPhysics3D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_BULLETPHYSICS3D_RIGIDBODY3D_HPP
#define NAZARA_BULLETPHYSICS3D_RIGIDBODY3D_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/BulletPhysics3D/Collider3D.hpp>
#include <Nazara/BulletPhysics3D/Config.hpp>
#include <Nazara/Core/Enums.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include <Nazara/Math/Quaternion.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/Utils/MovablePtr.hpp>

class btRigidBody;

namespace Nz
{
	class PhysWorld3D;

	class NAZARA_BULLETPHYSICS3D_API RigidBody3D
	{
		public:
			RigidBody3D(PhysWorld3D* world, const Matrix4f& mat = Matrix4f::Identity());
			RigidBody3D(PhysWorld3D* world, std::shared_ptr<Collider3D> geom, const Matrix4f& mat = Matrix4f::Identity());
			RigidBody3D(const RigidBody3D& object) = delete;
			RigidBody3D(RigidBody3D&& object) noexcept;
			~RigidBody3D();

			void AddForce(const Vector3f& force, CoordSys coordSys = CoordSys::Global);
			void AddForce(const Vector3f& force, const Vector3f& point, CoordSys coordSys = CoordSys::Global);
			void AddTorque(const Vector3f& torque, CoordSys coordSys = CoordSys::Global);

			void EnableAutoSleep(bool autoSleep);
			void EnableSimulation(bool simulation);

			Boxf GetAABB() const;
			float GetAngularDamping() const;
			Vector3f GetAngularVelocity() const;
			const std::shared_ptr<Collider3D>& GetGeom() const;
			float GetGravityFactor() const;
			float GetLinearDamping() const;
			Vector3f GetLinearVelocity() const;
			float GetMass() const;
			Vector3f GetMassCenter(CoordSys coordSys = CoordSys::Local) const;
			int GetMaterial() const;
			Matrix4f GetMatrix() const;
			Vector3f GetPosition() const;
			btRigidBody* GetRigidBody() const;
			Quaternionf GetRotation() const;
			void* GetUserdata() const;
			PhysWorld3D* GetWorld() const;

			bool IsAutoSleepEnabled() const;
			bool IsMoveable() const;
			bool IsSimulationEnabled() const;
			bool IsSleeping() const;

			void SetAngularDamping(float angularDamping);
			void SetAngularVelocity(const Vector3f& angularVelocity);
			void SetGeom(std::shared_ptr<Collider3D> geom, bool recomputeInertia = true);
			void SetGravityFactor(float gravityFactor);
			void SetLinearDamping(float damping);
			void SetLinearVelocity(const Vector3f& velocity);
			void SetMass(float mass);
			void SetMassCenter(const Vector3f& center);
			void SetPosition(const Vector3f& position);
			void SetRotation(const Quaternionf& rotation);

			RigidBody3D& operator=(const RigidBody3D& object) = delete;
			RigidBody3D& operator=(RigidBody3D&& object) noexcept;

		protected:
			void Destroy();

		private:
			std::shared_ptr<Collider3D> m_geom;
			std::unique_ptr<btRigidBody> m_body;
			PhysWorld3D* m_world;
	};
}

#endif // NAZARA_BULLETPHYSICS3D_RIGIDBODY3D_HPP
