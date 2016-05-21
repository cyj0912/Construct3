#include "SceneGraph.h"
#include "Shader.h"
#include <glm/gtc/matrix_inverse.hpp>
C3_NAMESPACE_BEGIN
extern FShader* Shader3D;

void SGCamera::Uniform(const glm::mat4& model)
{
	glm::mat4 matMV = MView * model;
	glm::mat4 matMVP = MProjection * matMV;
	glm::mat3 matNormal = glm::inverseTranspose(glm::mat3(matMV));
	Shader3D->Uniform(FShader::EUniformLocation::MV, value_ptr(matMV));
	Shader3D->Uniform(FShader::EUniformLocation::MVP, value_ptr(matMVP));
	Shader3D->Uniform(FShader::EUniformLocation::Normal, value_ptr(matNormal));
}
C3_NAMESPACE_END
