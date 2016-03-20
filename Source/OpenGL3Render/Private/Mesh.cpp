#include "Mesh.h"
#include <glad/glad.h>
C3_NAMESPACE_BEGIN
FMesh::FMesh()
{
}

void FMesh::Prepare()
{
    float Vertices[] = { 1.0f, 1.0f,
                         1.0f, -1.0f,
                         -1.0f, -1.0f,
                         -1.0f, 1.0f };
	//float Vertices[] = {
	//	30.0f, 30.0f,
	//	30.0f, 10.0f,
	//	10.0f, 10.0f,
	//	10.0f, 30.0f};
    float UVs[] = { 1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 1.0f };
    unsigned short Indices[] = { 0, 2, 1, 0, 3, 2 };
    glGenVertexArrays(1, &LocalVAO);
    glBindVertexArray(LocalVAO);
    glGenBuffers(1, &LocalVertices);
    glBindBuffer(GL_ARRAY_BUFFER, LocalVertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &LocalUVs);
    glBindBuffer(GL_ARRAY_BUFFER, LocalUVs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UVs), UVs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
    glEnableVertexAttribArray(1);
    glGenBuffers(1, &LocalIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LocalIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

void FMesh::Draw() const
{
    glBindVertexArray(LocalVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, LocalIndices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
}
C3_NAMESPACE_END
