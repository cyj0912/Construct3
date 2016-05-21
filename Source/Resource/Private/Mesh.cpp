#include "Mesh.h"
#include "File.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <algorithm>
C3_NAMESPACE_BEGIN
RMesh::RMesh()
{
	AABB.High = glm::vec3(0.0f);
	AABB.Low = glm::vec3(0.0f);
}

RMesh::RMesh(RResource *file)
{
	SetParent(file);
}

RMesh::RMesh(const std::string &identifier)
{
    const aiScene * scene = aiImportFile(RFile::GetPhysicalPath(identifier).c_str(),
		aiProcessPreset_TargetRealtime_Fast);
    aiMesh* mesh = scene->mMeshes[0];
	Vertices.reserve(mesh->mNumVertices * 3);
	Normals.reserve(mesh->mNumVertices * 3);
	UVs.reserve(mesh->mNumVertices * 2);
	Indices.reserve(mesh->mNumFaces * 3);
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertices.push_back(mesh->mVertices[i].x);
        Vertices.push_back(mesh->mVertices[i].y);
        Vertices.push_back(mesh->mVertices[i].z);
		AABB.High.x = std::max(AABB.High.x, mesh->mVertices[i].x);
		AABB.Low.x = std::min(AABB.Low.x, mesh->mVertices[i].x);
		AABB.High.y = std::max(AABB.High.y, mesh->mVertices[i].y);
		AABB.Low.y = std::min(AABB.Low.y, mesh->mVertices[i].y);
		AABB.High.z = std::max(AABB.High.z, mesh->mVertices[i].z);
		AABB.Low.z = std::min(AABB.Low.z, mesh->mVertices[i].z);
		if(mesh->HasNormals())
		{
			Normals.push_back(mesh->mNormals[i].x);
			Normals.push_back(mesh->mNormals[i].y);
			Normals.push_back(mesh->mNormals[i].z);
		}
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

const FAABB& RMesh::GetAABB()
{
	return AABB;
}

C3_NAMESPACE_END
