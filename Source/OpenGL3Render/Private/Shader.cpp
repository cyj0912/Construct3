﻿#include "Shader.h"
#include <glad/glad.h>
#include <File.h>
#include <vector>
#include <Log.h>

C3_NAMESPACE_BEGIN

FShader::FShader()
{
}

void FShader::Load()
{
	FFile vertSrc = FFile("color.v.glsl");
	char vertBuffer[4096];
	vertSrc.BufferRead(vertBuffer, sizeof(vertBuffer));
	FFile fragSrc = FFile("color.f.glsl");
	char fragBuffer[4096];
	fragSrc.BufferRead(fragBuffer, sizeof(fragBuffer));
	const char* bufArr[] = { vertBuffer, fragBuffer };

	int infoLogLength;
	std::vector<char> infoLog = std::vector<char>(4096);

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, bufArr, nullptr);
	glCompileShader(VertexShader);
	//glGetShaderInfoLog(VertexShader, 4096, &infoLogLength, infoLog.data());
	//FLog::Debug(infoLog.data());

	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, bufArr + 1, nullptr);
	glCompileShader(FragmentShader);
	//glGetShaderInfoLog(FragmentShader, 4096, &infoLogLength, infoLog.data());
	//FLog::Debug(infoLog.data());

	Program = glCreateProgram();
	glAttachShader(Program, VertexShader);
	glAttachShader(Program, FragmentShader);
	glLinkProgram(Program);
	glGetProgramInfoLog(Program, 4096, &infoLogLength, infoLog.data());
	FLog::Debug(infoLog.data());
}

void FShader::Bind()
{
	glUseProgram(Program);
}


C3_NAMESPACE_END
