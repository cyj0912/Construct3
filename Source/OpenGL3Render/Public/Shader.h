#pragma once
#include <Core.h>
#include <string>

C3_NAMESPACE_BEGIN
class FShader
{
	friend class FRender;
public:
    enum class EUniformLocation
    {
		MV,
        MVP,
		Normal,
		Glossy
    };
	FShader();
	void Load(const std::string& name);
	void Unload();
	void Bind() const;
	void Uniform(EUniformLocation loc, void* data) const;
private:
	unsigned int VertexShader, FragmentShader, Program;
};
C3_NAMESPACE_END
