#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <fstream>
#include <streambuf>
#include <glslang/Public/ShaderLang.h>

class Shader
{
public:
	Shader();
	~Shader();

	std::vector<char> CompileGLSLToSPIRV(const std::string& filename, EShLanguage shaderType);

private:
	EShLanguage GetShaderType(const std::string& filename);
};

#endif // !SHADER_H