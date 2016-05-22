#include "SceneGraph.h"
#include "Shader.h"
#include <glm/gtc/matrix_inverse.hpp>
#include "Model.h"
#include <Mesh.h>
#include <algorithm>
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

const FBoundingRect& SGObject::GetBoundingRectXY()
{
	size_t c = Model->GetRMesh()->Vertices.size();
	if (c % 3 != 0)
		throw "WTF has happened";
	BRect = FBoundingRect();
	size_t i = 0;
	{
		glm::vec3 p(Model->GetRMesh()->Vertices[i], Model->GetRMesh()->Vertices[i + 1], Model->GetRMesh()->Vertices[i + 2]);
		glm::vec4 hip = GetTransform() * glm::vec4(p, 1.0f);
		p = glm::vec3(hip) / hip.w;
		BRect.TopRight.x = p.x;
		BRect.TopRight.y = p.y;
		BRect.BtmLeft.x = p.x;
		BRect.BtmLeft.y = p.y;
	}
	for(i = 3; i < c; i += 3)
	{
		glm::vec3 p(Model->GetRMesh()->Vertices[i], Model->GetRMesh()->Vertices[i + 1], Model->GetRMesh()->Vertices[i + 2]);
		glm::vec4 hip = GetTransform() * glm::vec4(p, 1.0f);
		p = glm::vec3(hip) / hip.w;
		BRect.TopRight.x = max(BRect.TopRight.x, p.x);
		BRect.TopRight.y = max(BRect.TopRight.y, p.y);
		BRect.BtmLeft.x = min(BRect.BtmLeft.x, p.x);
		BRect.BtmLeft.y = min(BRect.BtmLeft.y, p.y);
	}
	return BRect;
}

void SGObject::Render()
{
	if(!bVisible)
		return;
	if (!Model)
		return;
	if (!bModelReady)
	{
		Model->Prepare();
		bModelReady = true;
	}
	Owner->GetActiveCamera()->Uniform(GetTransform());
	if(bRed)
		Shader3D->Uniform(FShader::EUniformLocation::Shading2, nullptr);
	else
		Shader3D->Uniform(FShader::EUniformLocation::Shading, nullptr);
	Model->Draw();
}

void SGObject::LoadModelFromResource(const FAutoRef<RMesh>& rmesh)
{
	Model = new FRenderModel(rmesh);
}

void SGObject::DeleteModel()
{
	delete Model;
	for(int i = 0; i < this->Parent->Children.size(); i++)
	{
		if(this->Parent->Children[i] == this)
		{
			this->Parent->Children.erase(this->Parent->Children.begin() + i);
			break;
		}
	}
	delete this;
}
C3_NAMESPACE_END
