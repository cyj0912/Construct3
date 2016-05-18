#pragma once
#include <Core.h>

C3_NAMESPACE_BEGIN
class FShader
{
public:
    enum class EUniformLocation
    {
        MVP
    };
	FShader();
	void Load();
	void Bind();
	void Uniform(EUniformLocation loc, void* data);
public:
	unsigned int VertexShader, FragmentShader, Program;
};
C3_NAMESPACE_END
