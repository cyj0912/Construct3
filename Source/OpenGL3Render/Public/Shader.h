#pragma once
#include <Core.h>

C3_NAMESPACE_BEGIN
class FShader
{
public:
	FShader();
	void Load();
	void Bind();

public:
	unsigned int VertexShader, FragmentShader, Program;
};
C3_NAMESPACE_END
