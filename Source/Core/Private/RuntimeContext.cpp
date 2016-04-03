#include <RuntimeContext.h>
#include "System.h"

namespace c3
{

void FRuntimeContext::Construct()
{
	RC.System = new FSystem;
}

FRuntimeContext RC;

}
