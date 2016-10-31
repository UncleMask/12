#pragma once
#include<string>
#include<vector>
#include"HResult.h"
namespace xhr {
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
		virtual xhr::HResult init(FILE *fp) = 0;
		statemachine();
		statemachine(int i);
		std::vector<state<TYPE>*> statelist;
		xhr::HResult Input(TYPE t);
		xhr::HResult Append(node<TYPE>* p);
		xhr::HResult Append(int loc,//״̬
			TYPE inp,//����
			int dns);//Ŀ��״̬
		xhr::HResult Append();
		~statemachine();
	private:
		int location = 0;
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
	inline xhr::HResult statemachine<TYPE>::Input(TYPE t)
	{
		xhr::HResult res;
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
		xhr::HResult res;
		state<TYPE> * s = new state<TYPE>(p);
		statelist.push_back(s);
		return xhr::HResult();
	}
	//���ת��
	template<typename TYPE>
	inline xhr::HResult statemachine<TYPE>::Append(int loc, TYPE inp, int dns)
	{
		node<TYPE> *p = statelist.at(loc)->p;
		if (p == nullptr) {
			statelist.at(loc)->p = new node<TYPE>(inp,
				dns);
			return xhr::HResult();
		}
		else {
			for (;;) {
				if (p->pNext == nullptr) break;
				p = p->pNext;
			}
			p->pNext = new node<TYPE>(inp,
				dns);
			return xhr::HResult();
		}
	}
	//���״̬
	template<typename TYPE>
	inline xhr::HResult statemachine<TYPE>::Append()
	{
		xhr::HResult res;
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

}
