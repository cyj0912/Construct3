#pragma once
#include <Core.h>
#include <iostream>
#include <fstream>
C3_NAMESPACE_BEGIN
class FLog
{
public:
	static void Debug(const char* msg)
	{
		std::fstream of = std::fstream("output.log", std::ios::app);
		of << "------------------ Log ------------------" << std::endl;
		of << msg << std::endl;
		of.close();
	}
};
C3_NAMESPACE_END
