#pragma once
#include <Core.h>
#include <OpenGL3Render/Public/SceneGraph.h>

C3_NAMESPACE_BEGIN
class IEntity {
public:
	SGObject* SGEntry;
	virtual void Update() = 0;
	virtual void Init() = 0;
};

class FPlayer : public IEntity {
public:
	void Update() override;
	void Init() override;
};

class FEnemy : public IEntity {
public:
	void Update() override;
	void Init() override;
};
C3_NAMESPACE_END
