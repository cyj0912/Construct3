#include <Core.h>
#include "Engine.h"
C3_NAMESPACE_BEGIN
void FEngine::Update()
{
	RC.System->GetSystemClock()->Tick();
}

void FEngine::StartGame()
{
	
}
C3_NAMESPACE_END
