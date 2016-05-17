#include <Log.h>
#include <RuntimeContext.h>
#include <IEditor.h>
#include <sstream>
C3_NAMESPACE_BEGIN
struct FLogDataBuffer
{
    std::stringstream SS;
};
static FLogDataBuffer DataBuffer;

std::string FLog::ReadBuffer()
{
	std::string tempBuffer;
	tempBuffer = DataBuffer.SS.str();
	DataBuffer.SS.str(std::string());
	if (tempBuffer[tempBuffer.length() - 1] == '\n')
		tempBuffer.erase(tempBuffer.size() - 1);
	return tempBuffer;
}

void FLog::Debug(const char* msg)
{
    DataBuffer.SS << msg << std::endl;

	if(RC.Editor && RC.Editor->GetLogDisplay())
    	RC.Editor->GetLogDisplay()->Refresh();
}
C3_NAMESPACE_END
