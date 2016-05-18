#pragma once
#include <Core.h>

C3_NAMESPACE_BEGIN
class FShader
{
public:
    enum class EUniformLocation
    {
		MV,
        MVP,
		Normal
    };
	FShader();
	void Load();
	void Unload();
	void Bind() const;
	void Uniform(EUniformLocation loc, void* data) const;
private:
	unsigned int VertexShader, FragmentShader, Program;
};
C3_NAMESPACE_END
