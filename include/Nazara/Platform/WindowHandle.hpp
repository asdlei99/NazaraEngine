// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Platform module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_PLATFORM_WINDOWHANDLE_HPP
#define NAZARA_PLATFORM_WINDOWHANDLE_HPP

#include <NazaraUtils/Prerequisites.hpp>
#include <Nazara/Utility/Config.hpp>

namespace Nz
{
	enum class WindowBackend
	{
		Invalid,

		Cocoa,
		X11,
		Wayland,
		Web,
		Windows
	};

	struct WindowHandle
	{
		WindowBackend type = WindowBackend::Invalid;

		union
		{
			struct
			{
				void* window; //< NSWindow*
			} cocoa;

			struct
			{
				void* display; //< Display*
				unsigned long window;  //< Window
			} x11;

			struct
			{
				void* display;      //< wl_display*
				void* surface;      //< wl_surface*
				void* shellSurface; //< wl_shell_surface*
			} wayland;

			struct
			{
				void* window; //< HWND
			} windows;

		};
	};
}

#endif // NAZARA_PLATFORM_WINDOWHANDLE_HPP
