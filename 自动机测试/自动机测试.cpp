// 自动机测试.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "statemachine.h"

int main()
{
	statemachine<char> sm1;
	sm1.Append();
	sm1.Append();
	sm1.Append(0, 'a', 1);
	sm1.Append(0, 'b', 2);
	sm1.Input('a');
    return 0;
}

