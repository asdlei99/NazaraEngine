// Copyright (C) 2023 Jérôme "Lynix" Leclercq (lynix680@gmail.com)
// This file is part of the "Nazara Engine - Utility module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Utility/Debug.hpp>

namespace Nz
{
	inline std::size_t AbstractTextDrawer::GetLineGlyphCount(std::size_t index) const
	{
		std::size_t lineCount = GetLineCount();
		const auto& lineInfo = GetLine(index);
		if (index == lineCount - 1)
			return GetGlyphCount() - lineInfo.glyphIndex;

		const auto& nextLineInfo = GetLine(index + 1);

		return nextLineInfo.glyphIndex - lineInfo.glyphIndex;
	}
}

#include <Nazara/Utility/DebugOff.hpp>
