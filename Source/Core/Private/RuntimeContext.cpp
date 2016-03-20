#include <RuntimeContext.h>
#include "System.h"

namespace c3
{

void FRuntimeContext::Construct()
{
	RuntimeContext.System = new FSystem;
}

FRuntimeContext RuntimeContext;

}
