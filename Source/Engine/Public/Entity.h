#pragma once
#include <Core.h>
#include <OpenGL3Render/Public/SceneGraph.h>

C3_NAMESPACE_BEGIN
class IEntity {
public:
	SGObject* SGEntry;
	virtual void Update() = 0;
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	const FBoundingRect* BoundingRect;
	uint32_t LastBoundingUpdate = 0;
	virtual const FBoundingRect& GetBoundingRect();
};

class FPlayer : public IEntity {
public:
	void Update() override;
	void Init() override;
	void Destroy() override;
};

class FEnemy : public IEntity {
public:
	void Update() override;
	void Init() override;
	void Destroy() override;
};
C3_NAMESPACE_END
