#pragma once
#include <Core.h>
#include "Resource.h"
#include <vector>
#include <glm/glm.hpp>
C3_NAMESPACE_BEGIN
struct FAABB
{
	glm::vec3 High, Low;
};

class RMesh : public RResource
{
    friend class FRenderModel;
public:
    RMesh();
    RMesh(RResource* file);
    RMesh(const std::string& identifier);
    ~RMesh();
    void LoadMesh();
	const FAABB& GetAABB();

public:
    std::vector<float> Vertices;
    std::vector<unsigned short> Indices;
    std::vector<float> UVs;
	std::vector<float> Normals;
	FAABB AABB;
};
C3_NAMESPACE_END
