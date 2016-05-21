#pragma once
#include <Core.h>
#include <glad/glad.h>
C3_NAMESPACE_BEGIN
class RMesh;
class FRenderModel
{
public:
    FRenderModel();
    explicit FRenderModel(const FAutoRef<RMesh> & mesh);
    ~FRenderModel();
    void Prepare();
    void Draw() const;
	const FAutoRef<RMesh>& GetRMesh();
private:
    FAutoRef<RMesh> ResourceRef;
	GLuint LocalVAO, LocalVertices, LocalUVs, LocalIndices, LocalNormals;
};
C3_NAMESPACE_END
