#pragma once
#include <Core.h>
#include <glad/glad.h>
C3_NAMESPACE_BEGIN
class RMesh;
class FRenderModel
{
public:
    FRenderModel();
    FRenderModel(const FAutoRefPtr<RMesh> & mesh);
    ~FRenderModel();
    void Prepare();
    void Draw() const;
private:
    FAutoRefPtr<RMesh> ResourceRef;
    GLuint LocalVAO, LocalVertices, LocalUVs, LocalIndices;
};
C3_NAMESPACE_END
