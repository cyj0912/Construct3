#include "Shader.h"
#include <glad/glad.h>
#include <File.h>
#include <vector>
#include <Log.h>

C3_NAMESPACE_BEGIN

FShadingUniform ShadingState;

FShader::FShader(): VertexShader(0), FragmentShader(0), Program(0)
{
	memset(&ShadingState, 0, sizeof(ShadingState));
	ShadingState.lights[0].bEnabled = true;
	ShadingState.lights[0].intensity = vec3(1.0);
	ShadingState.lights[0].ecPosOrDir = vec3(0.0);
	ShadingState.material.baseColor = vec3(0.55, 0.99, 0.66);
	ShadingState.material.specular = vec3(1.0);
	ShadingState.material.roughness = 0.25f;
	ShadingState.material.metallic = 0.75f;
}

void FShader::Load(const std::string& name)
{
	RFile vertSrc = RFile(name + std::string(".v.glsl"));
	char vertBuffer[4096];
	vertSrc.BufferRead(vertBuffer, sizeof(vertBuffer));
	RFile fragSrc = RFile(name + std::string(".f.glsl"));
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
	{
		FLog::Debug(infoLog.data());
		return;
	}

	int ULocation = glGetUniformBlockIndex(Program, "Shading");
	int datasize;
	glGetActiveUniformBlockiv(Program, ULocation, GL_UNIFORM_BLOCK_DATA_SIZE, &datasize);
	glUniformBlockBinding(Program, ULocation, 0);

	glGenBuffers(1, &UBOShading);
	glBindBuffer(GL_UNIFORM_BUFFER, UBOShading);
	glBufferData(GL_UNIFORM_BUFFER, datasize, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, datasize, &ShadingState);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBOShading);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void FShader::Unload()
{
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	glDeleteProgram(Program);
	glDeleteBuffers(1, &UBOShading);
}

void FShader::Bind() const
{
	glUseProgram(Program);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBOShading);
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
	case EUniformLocation::Shading:
		break;
    }
}
C3_NAMESPACE_END
