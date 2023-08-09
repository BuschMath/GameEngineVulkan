#ifndef SHADER_COMPILER_H
#define SHADER_COMPILER_H

#include <vector>
#include <fstream>
#include <streambuf>
#include <glslang/Public/ShaderLang.h>

class ShaderCompiler
{
public:
	ShaderCompiler();
	~ShaderCompiler();

	std::vector<char> CompileGLSLToSPIRV(const std::string& filename, EShLanguage shaderType);

private:
	EShLanguage GetShaderType(const std::string& filename);
};

#endif // !SHADER_COMPILER_H