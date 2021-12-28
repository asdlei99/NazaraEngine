#include <Engine/Shader/ShaderUtils.hpp>
#include <Nazara/Core/File.hpp>
#include <Nazara/Core/StringExt.hpp>
#include <Nazara/Shader/ShaderBuilder.hpp>
#include <Nazara/Shader/ShaderLangParser.hpp>
#include <catch2/catch.hpp>
#include <cctype>

TEST_CASE("loops", "[Shader]")
{
	std::string_view nzslSource = R"(
struct inputStruct
{
	value: f32
}

external
{
	[set(0), binding(0)] data: uniform<inputStruct>
}

[entry(frag)]
fn main()
{
	let value = 0.0;
	let i = 0;
	while (i < 10)
	{
		value += 0.1;
		i += 1;
	}
}
)";

	Nz::ShaderAst::StatementPtr shader = Nz::ShaderLang::Parse(nzslSource);

	ExpectGLSL(*shader, R"(
void main()
{
	float value = 0.000000;
	int i = 0;
	while (i < (10))
	{
		value += 0.100000;
		i += 1;
	}
	
}
)");

	ExpectNZSL(*shader, R"(
[entry(frag)]
fn main()
{
	let value: f32 = 0.000000;
	let i: i32 = 0;
	while (i < (10))
	{
		value += 0.100000;
		i += 1;
	}
	
}
)");

	ExpectSpirV(*shader, R"(
OpFunction
OpLabel
OpVariable
OpVariable
OpStore
OpStore
OpBranch
OpLabel
OpLoad
OpSLessThan
OpLoopMerge
OpBranchConditional
OpLabel
OpLoad
OpFAdd
OpStore
OpLoad
OpIAdd
OpStore
OpBranch
OpLabel
OpReturn
OpFunctionEnd)");
}