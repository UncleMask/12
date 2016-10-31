#pragma once
#include<string>
#include<vector>
#include"HResult.h"
template<typename TYPE>
class node {
public:
	node(TYPE ch,
		 int i1) {
		content = ch;
		i = i1;
	}
	TYPE content;
	int i;
	node<TYPE>* pNext;
};

template<typename TYPE>
class state {
public:
	state(node<TYPE> *p1) {
		p = p1;
	}
	state();
	int name;
	node<TYPE>* p;
};

template<typename TYPE>
class statemachine
{
public:
	//virtual HResult init(FILE *fp)=0;
	statemachine();
	statemachine(int i);

	vector<state<TYPE>*> statelist;
	HResult Input(TYPE t);
	HResult Append(node<TYPE>* p);
	HResult Append(int loc,//状态
				   TYPE inp,//输入
				   int dns);//目标状态
	HResult Append();
	~statemachine();
private:
	int location=0;
};


template<typename TYPE>
inline statemachine<TYPE>::statemachine()
{
}
template<typename TYPE>
inline statemachine<TYPE>::statemachine(int i)
{
}

//无效转移返回not found
//有效转移返回i值为状态
template<typename TYPE>
inline HResult statemachine<TYPE>::Input(TYPE t)
{
	HResult res;
	node<TYPE>* p = statelist.at(location)->p;
	for (;;) {
		if (p->content == t)
		{
			location = p->i;
			res.i = location;
			return res;
		}
		if (p->pNext == nullptr) {
			res.info = "not found";
			res.i = -1;
			return res;
		}
		p = p->pNext;
	}
}

//添加带转移状态
template<typename TYPE>
inline HResult statemachine<TYPE>::Append(node<TYPE> * p)
{
	HResult res;
	state<TYPE> * s = new state<TYPE>(p);
	statelist.push_back(s);
	return HResult();
}
//添加转移
template<typename TYPE>
inline HResult statemachine<TYPE>::Append(int loc,
										TYPE inp,
										int dns)
{
	node<TYPE> *p = statelist.at(loc)->p;
	if (p == nullptr) {
		statelist.at(loc)->p = new node<TYPE>(inp,
			dns);
		return HResult();
	}
	else {
		for (;;) {
			if (p->pNext == nullptr) break;
			p = p->pNext;
		}
		p->pNext = new node<TYPE>(inp,
			dns);
		return HResult();
	}
}
//添加状态
template<typename TYPE>
inline HResult statemachine<TYPE>::Append()
{
	HResult res;
	state<TYPE> * s = new state<TYPE>();
	statelist.push_back(s);

	return res;
}

template<typename TYPE>
inline statemachine<TYPE>::~statemachine()
{
}

template<typename TYPE>
inline state<TYPE>::state()
{
}
