#pragma once
#include <Core.h>
#include <glad/glad.h>
C3_NAMESPACE_BEGIN
class RMesh;
class FRenderMesh
{
public:
    FRenderMesh();
    FRenderMesh(RMesh* mesh);
    ~FRenderMesh();
    void Prepare();
    void Draw() const;
private:
    RMesh* Resource;
    GLuint LocalVAO, LocalVertices, LocalUVs, LocalIndices;
};
C3_NAMESPACE_END
