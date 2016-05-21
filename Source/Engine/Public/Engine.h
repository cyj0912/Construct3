#pragma once
#include <Core.h>
#include <Resource/Public/Mesh.h>

C3_NAMESPACE_BEGIN
class FEngine
{
public:
	FAutoRef<RMesh> BunnyRMesh;

	FEngine()
	{}
	~FEngine()
	{}
	void Update();
	void Init();
};
C3_NAMESPACE_END
