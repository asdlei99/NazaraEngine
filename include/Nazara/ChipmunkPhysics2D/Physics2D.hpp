// Copyright (C) 2022 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - ChipmunkPhysics2D module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CHIPMUNKPHYSICS2D_PHYSICS2D_HPP
#define NAZARA_CHIPMUNKPHYSICS2D_PHYSICS2D_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/ChipmunkPhysics2D/Config.hpp>
#include <Nazara/Core/Core.hpp>

namespace Nz
{
	class NAZARA_CHIPMUNKPHYSICS2D_API Physics2D : public ModuleBase<Physics2D>
	{
		friend ModuleBase;

		public:
			using Dependencies = TypeList<Core>;

			struct Config {};

			Physics2D(Config /*config*/);
			~Physics2D() = default;

		private:
			static Physics2D* s_instance;
	};
}

#endif // NAZARA_CHIPMUNKPHYSICS2D_PHYSICS2D_HPP
