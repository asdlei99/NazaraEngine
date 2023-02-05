// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Core module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_CORE_APPFILESYSTEMCOMPONENT_HPP
#define NAZARA_CORE_APPFILESYSTEMCOMPONENT_HPP

#include <Nazara/Prerequisites.hpp>
#include <Nazara/Core/ApplicationComponent.hpp>
#include <Nazara/Core/Config.hpp>
#include <Nazara/Core/ResourceParameters.hpp>
#include <Nazara/Core/VirtualDirectory.hpp>
#include <memory>
#include <vector>

namespace Nz
{
	class Font;
	class Image;
	class ImageStream;
	class Material;
	class MaterialInstance;
	class Mesh;
	class SoundBuffer;
	class SoundStream;
	class Texture;

	class NAZARA_CORE_API AppFilesystemComponent : public ApplicationComponent
	{
		public:
			inline AppFilesystemComponent(ApplicationBase& app);
			AppFilesystemComponent(const AppFilesystemComponent&) = delete;
			AppFilesystemComponent(AppFilesystemComponent&&) = delete;
			~AppFilesystemComponent() = default;

			template<typename T> const typename T::Params* GetDefaultResourceParameters() const;

			template<typename T> std::shared_ptr<T> Load(std::string_view assetPath);
			template<typename T> std::shared_ptr<T> Load(std::string_view assetPath, typename T::Params params);

			inline const VirtualDirectoryPtr& Mount(std::string_view name, std::filesystem::path filepath);
			inline const VirtualDirectoryPtr& Mount(std::string_view name, VirtualDirectoryPtr directory);

			template<typename T> std::shared_ptr<T> Open(std::string_view assetPath);
			template<typename T> std::shared_ptr<T> Open(std::string_view assetPath, typename T::Params params);

			template<typename T> void SetDefaultResourceParameters(typename T::Params params);

			AppFilesystemComponent& operator=(const AppFilesystemComponent&) = delete;
			AppFilesystemComponent& operator=(AppFilesystemComponent&&) = delete;

			static inline void RegisterResourceTypes();

		private:
			template<typename T> std::shared_ptr<T> LoadImpl(std::string_view assetPath, const typename T::Params& params);
			template<typename T> std::shared_ptr<T> OpenImpl(std::string_view assetPath, const typename T::Params& params);

			std::vector<std::unique_ptr<ResourceParameters>> m_defaultParameters;
			VirtualDirectoryPtr m_rootDirectory;
	};
}

#include <Nazara/Core/AppFilesystemComponent.inl>

#endif // NAZARA_CORE_APPFILESYSTEMCOMPONENT_HPP