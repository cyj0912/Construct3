#pragma once
#include <Core.h>
#include "Resource.h"
#include <vector>
C3_NAMESPACE_BEGIN
class RMesh : public RResource
{
    friend class FRenderModel;
public:
    RMesh();
    RMesh(RResource* file);
    RMesh(const std::string& identifier);
    ~RMesh();
    void LoadMesh();

private:
    std::vector<float> Vertices;
    std::vector<unsigned short> Indices;
    std::vector<float> UVs;
	std::vector<float> Normals;
};
C3_NAMESPACE_END
