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
	HResult Append(int loc,//״̬
				   TYPE inp,//����
				   int dns);//Ŀ��״̬
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

//��Чת�Ʒ���not found
//��Чת�Ʒ���iֵΪ״̬
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

//��Ӵ�ת��״̬
template<typename TYPE>
inline HResult statemachine<TYPE>::Append(node<TYPE> * p)
{
	HResult res;
	state<TYPE> * s = new state<TYPE>(p);
	statelist.push_back(s);
	return HResult();
}
//���ת��
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
//���״̬
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
