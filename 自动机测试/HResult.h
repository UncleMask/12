#pragma once
#include<string>
namespace xhr {
	class HResult
	{
	public:
		int i;
		std::string info;
		HResult(std::string str, int i1);
		HResult();
		~HResult();
	};
}

