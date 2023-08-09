#include "ShaderCompiler.h"

ShaderCompiler::ShaderCompiler()
{
	glslang::InitializeProcess();
}

ShaderCompiler::~ShaderCompiler()
{
	glslang::FinalizeProcess();
}

std::vector<char> ShaderCompiler::CompileGLSLToSPIRV(const std::string& filename, EShLanguage shaderType)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file");
	}
	
	std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	
	const char* shaderSource = source.c_str();
	
	glslang::TShader shader(shaderType);
	shader.setStrings(&shaderSource, 1);
	
	TBuiltInResource resources = {};

	if (!shader.parse(&resources, 100, false, EShMsgDefault)) {
		throw std::runtime_error("Failed to parse shader");
	}
	
	glslang::TProgram program;
	program.addShader(&shader);
	
	if (!program.link(EShMsgDefault)) {
		throw std::runtime_error("Failed to link shader");
	}
}

EShLanguage ShaderCompiler::GetShaderType(const std::string& filename)
{
	return EShLanguage();
}
