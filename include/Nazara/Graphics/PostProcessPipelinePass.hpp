// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Graphics module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_GRAPHICS_POSTPROCESSPIPELINEPASS_HPP
#define NAZARA_GRAPHICS_POSTPROCESSPIPELINEPASS_HPP

#include <NazaraUtils/Prerequisites.hpp>
#include <Nazara/Graphics/Config.hpp>
#include <Nazara/Graphics/FramePipelinePass.hpp>
#include <Nazara/Graphics/UberShader.hpp>

namespace Nz
{
	class FrameGraph;
	class FramePass;
	class FramePipeline;
	class RenderFrame;
	class RenderPipeline;
	class ShaderBinding;

	class NAZARA_GRAPHICS_API PostProcessPipelinePass : public FramePipelinePass
	{
		public:
			PostProcessPipelinePass(FramePipeline& owner, std::string passName, std::string shaderName);
			PostProcessPipelinePass(const PostProcessPipelinePass&) = delete;
			PostProcessPipelinePass(PostProcessPipelinePass&&) = delete;
			~PostProcessPipelinePass() = default;

			void Prepare(RenderFrame& renderFrame);

			FramePass& RegisterToFrameGraph(FrameGraph& frameGraph, std::size_t inputColorBufferIndex, std::size_t outputColorBufferIndex);

			PostProcessPipelinePass& operator=(const PostProcessPipelinePass&) = delete;
			PostProcessPipelinePass& operator=(PostProcessPipelinePass&&) = delete;

		private:
			void BuildPipeline();

			NazaraSlot(UberShader, OnShaderUpdated, m_onShaderUpdated);

			std::shared_ptr<RenderPipelineLayout> m_renderPipelineLayout;
			std::shared_ptr<RenderPipeline> m_renderPipeline;
			std::shared_ptr<RenderPipeline> m_nextRenderPipeline;
			std::shared_ptr<ShaderBinding> m_shaderBinding;
			std::string m_passName;
			UberShader m_shader;
			FramePipeline& m_pipeline;
			bool m_rebuildFramePass;
	};
}

#include <Nazara/Graphics/PostProcessPipelinePass.inl>

#endif // NAZARA_GRAPHICS_POSTPROCESSPIPELINEPASS_HPP
