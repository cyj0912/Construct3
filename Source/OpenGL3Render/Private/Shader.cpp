#include "Shader.h"
#include <glad/glad.h>
#include <File.h>
#include <vector>
#include <Log.h>

C3_NAMESPACE_BEGIN

FShader::FShader(): VertexShader(0), FragmentShader(0), Program(0)
{
}

void FShader::Load()
{
	RFile vertSrc = RFile("brdf.v.glsl");
	char vertBuffer[4096];
	vertSrc.BufferRead(vertBuffer, sizeof(vertBuffer));
	RFile fragSrc = RFile("brdf.f.glsl");
	char fragBuffer[4096];
	fragSrc.BufferRead(fragBuffer, sizeof(fragBuffer));
	const char* bufArr[] = { vertBuffer, fragBuffer };

	int infoLogLength;
	std::vector<char> infoLog = std::vector<char>(4096);

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, bufArr, nullptr);
	glCompileShader(VertexShader);
	glGetShaderInfoLog(VertexShader, 4096, &infoLogLength, infoLog.data());
	if(infoLogLength != 0)
		FLog::Debug(infoLog.data());

	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, bufArr + 1, nullptr);
	glCompileShader(FragmentShader);
	glGetShaderInfoLog(FragmentShader, 4096, &infoLogLength, infoLog.data());
	if (infoLogLength != 0)
		FLog::Debug(infoLog.data());

	Program = glCreateProgram();
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glLinkProgram(Program);
	glGetProgramInfoLog(Program, 4096, &infoLogLength, infoLog.data());
	if (infoLogLength != 0)
		FLog::Debug(infoLog.data());
}

void FShader::Unload()
{
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	glDeleteProgram(Program);
}

void FShader::Bind() const
{
	glUseProgram(Program);
}

void FShader::Uniform(EUniformLocation loc, void *data) const
{
	GLint uniformLoc;
	switch (loc)
    {
	case EUniformLocation::MV:
		uniformLoc = glGetUniformLocation(Program, "uMV");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, (const GLfloat*)data);
		break;
	case EUniformLocation::MVP:
		uniformLoc = glGetUniformLocation(Program, "uMVP");
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, (const GLfloat*)data);
        break;
    case EUniformLocation::Normal:
		uniformLoc = glGetUniformLocation(Program, "uMNormal");
		glUniformMatrix3fv(uniformLoc, 1, GL_FALSE, (const GLfloat*)data);
		break;
    default: break;
    }
}
C3_NAMESPACE_END
