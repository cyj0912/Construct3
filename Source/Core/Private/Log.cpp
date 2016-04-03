#include <Log.h>
#include <iostream>
#include <fstream>
C3_NAMESPACE_BEGIN
void FLog::Debug(const char* msg)
{
	static bool first = true;
	std::fstream of = std::fstream("output.log", std::ios::app);
	if (first)
	{
		of << "------------------ Log ------------------" << std::endl;
		first = false;
	}
	of << msg << std::endl;
	of.close();
}
C3_NAMESPACE_END
