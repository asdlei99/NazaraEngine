// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - ChipmunkPhysics2D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CHIPMUNKPHYSICS2D_ARBITER2D_HPP
#define NAZARA_CHIPMUNKPHYSICS2D_ARBITER2D_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/ChipmunkPhysics2D/Config.hpp>
#include <Nazara/Math/Vector2.hpp>
#include <Nazara/Utils/MovablePtr.hpp>

struct cpArbiter;

namespace Nz
{
	class RigidBody2D;

	class NAZARA_CHIPMUNKPHYSICS2D_API Arbiter2D
	{
		public:
			inline Arbiter2D(cpArbiter* arbiter);
			Arbiter2D(const Arbiter2D&) = delete;
			Arbiter2D(Arbiter2D&&) = default;
			~Arbiter2D() = default;

			float ComputeTotalKinematicEnergy() const;
			Nz::Vector2f ComputeTotalImpulse() const;

			std::pair<RigidBody2D*, RigidBody2D*> GetBodies() const;

			std::size_t GetContactCount() const;
			float GetContactDepth(std::size_t i) const;
			Vector2f GetContactPointA(std::size_t i) const;
			Vector2f GetContactPointB(std::size_t i) const;

			float GetElasticity() const;
			float GetFriction() const;
			Vector2f GetNormal() const;
			Vector2f GetSurfaceVelocity() const;

			bool IsFirstContact() const;
			bool IsRemoval() const;

			void SetElasticity(float elasticity);
			void SetFriction(float friction);
			void SetSurfaceVelocity(const Vector2f& surfaceVelocity);

			Arbiter2D& operator=(const Arbiter2D&) = delete;
			Arbiter2D& operator=(Arbiter2D&&) = default;

		private:
			MovablePtr<cpArbiter> m_arbiter;
	};
}

#include <Nazara/ChipmunkPhysics2D/Arbiter2D.inl>

#endif // NAZARA_CHIPMUNKPHYSICS2D_ARBITER2D_HPP
