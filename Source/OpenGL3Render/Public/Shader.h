#pragma once
#include <Core.h>
#include <string>
#include <glm/glm.hpp>

C3_NAMESPACE_BEGIN
using glm::vec3;

struct FShaderLight
{
	bool bEnabled; char p[3];
	bool bIsDirectional; char q[11];
	vec3 ecPosOrDir; char r[4];
	vec3 intensity; char s[4];
};

struct FShaderMaterial
{
	vec3 baseColor; char r[4];
	vec3 specular;
	float roughness;
	float metallic;
};

struct FShadingUniform
{
	FShaderLight lights[4];
	FShaderMaterial material;
};

class FShader
{
	friend class FRender;
public:
    enum class EUniformLocation
    {
		MV,
        MVP,
		Normal,
		Shading
    };
	FShader();
	void Load(const std::string& name);
	void Unload();
	void Bind() const;
	void Uniform(EUniformLocation loc, void* data) const;
private:
	unsigned int VertexShader, FragmentShader, Program, UBOShading;
};
C3_NAMESPACE_END
