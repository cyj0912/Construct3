#include "Scene.h"
#include "Actor.h"
#include "Component.h"
#include "Camera.h"
#include "Engine.h"
#include <Log.h>
C3_NAMESPACE_BEGIN
C3_DEFINE_ENTITY(EScene)

EScene::EScene()
{
}

EScene::~EScene()
{
}

void EScene::Spawn(FEntityRef parent)
{
    EEntity::Spawn(parent);
    if(parent == nullptr)
        this->SetParent(this);

    AActor* a = RC.Engine->GetEntityManager().NewEntity<AActor>();
    a->Spawn(this);

    CTransform* ct = RC.Engine->GetEntityManager().NewEntity<CTransform>();
    a->AttachComponent(ct);
    a->PrintCompInfo();

	ACamera* cam = RC.Engine->GetEntityManager().NewEntity<ACamera>();
	cam->Spawn(this);
	cam->PrintCompInfo();

    PrintSceneInfo(this, "", true);
}

void EScene::Update()
{
    EEntity::Update();
}

void EScene::PrintSceneInfo(FEntityRef node, std::string indent, bool last)
{
	if(node->GetParent() == node)
	{
		FLog::Debug(std::string(node->GetEntityInfo()->ClassName).c_str());
	}
	else
	{
		FLog::Debug((indent + "+-" + node->GetEntityInfo()->ClassName).c_str());
		if (last)
			indent += "  ";
		else
			indent += "| ";
	}
	int n = 1;
	for(FChildren::iterator iter = node->GetBeginChild(); iter != node->GetEndChild(); ++iter)
	{
		PrintSceneInfo(*iter, indent, n == node->CountChildren());
		n++;
	}
}
C3_NAMESPACE_END
