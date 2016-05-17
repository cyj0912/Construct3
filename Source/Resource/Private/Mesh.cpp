#include "Mesh.h"
#include "File.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
C3_NAMESPACE_BEGIN
RMesh::RMesh()
{
}

RMesh::RMesh(RResource *file)
{
	SetParent(file);
}

RMesh::RMesh(const std::string &identifier)
{
    const aiScene * scene = aiImportFile(RFile::GetPhysicalPath(identifier).c_str(),
                                         aiProcessPreset_TargetRealtime_MaxQuality);
    aiMesh* mesh = scene->mMeshes[0];
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertices.push_back(mesh->mVertices[i].x);
        Vertices.push_back(mesh->mVertices[i].y);
        Vertices.push_back(mesh->mVertices[i].z);
        if(mesh->HasTextureCoords(0))
        {
            UVs.push_back(mesh->mTextureCoords[0][i].x);
            UVs.push_back(mesh->mTextureCoords[0][i].y);
        }
        else
        {
            UVs.push_back((float)i * (1 / (float)mesh->mNumVertices));
            UVs.push_back((mesh->mNumVertices - i) * (1 / (float)mesh->mNumVertices));
        }
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        Indices.push_back(mesh->mFaces[i].mIndices[0]);
        Indices.push_back(mesh->mFaces[i].mIndices[1]);
        Indices.push_back(mesh->mFaces[i].mIndices[2]);
    }
    aiReleaseImport(scene);
}

RMesh::~RMesh()
{
}

void RMesh::LoadMesh()
{
	if (Parent)
		return;
}

C3_NAMESPACE_END
