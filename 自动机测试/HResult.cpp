#include "HResult.h"
using namespace xhr;
HResult::HResult(std::string str, int i1)
{
	this->info = str;
	this->i = i1;
}

HResult::HResult()
{
}


HResult::~HResult()
{
}
