#pragma once
#include <Core.h>
#include <glad/glad.h>
C3_NAMESPACE_BEGIN
class FMesh
{
public:
    FMesh();
    void Prepare();
    void Draw() const;
private:
    GLuint LocalVAO, LocalVertices, LocalUVs, LocalIndices;
};
C3_NAMESPACE_END
