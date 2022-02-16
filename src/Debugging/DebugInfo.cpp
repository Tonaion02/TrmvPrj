#include "DebugInfo.h"

#include "ECS/EntityManager.h"





void debugInfoEntity()
{
	printf("%d\n", static_cast<int>(EntityManager::get().mDeadEntities.size()) );
}