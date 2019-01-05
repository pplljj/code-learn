#include<iostream>
//#include<string>

using namespace std;

namespace bs{

	typedef struct people{
		int val;
		struct people* pnext;
		people();
	}node;

	people::people() :val(0), pnext(0){}

	typedef struct basestack{
		node* bottom;
		node* top;
		basestack();
	}bsk;

	basestack::basestack() :bottom(0), top(0){}

	void printlist(bsk* bskk)
	{
		node* p = bskk->top;
		while (1)
		{
			if (!p) return;
			cout << p->val << " ";
			if (p == bskk->bottom) break;
			p = p->pnext;
		}
		cout << "\n";
	}

	bsk* push_in_stack(int value, bsk* bskk)
	{
		node* tp = new node;
		tp->val = value;

		if (bskk->top == NULL)
		{
			bskk->bottom = tp;
			bskk->top = tp;
			return bskk;
		}
		else{
			tp->pnext = bskk->top;
			bskk->top = tp;
			return bskk;
		}
	}

	bsk* pop_out_stack(node& res, bsk* bskk)
	{
		node* p = bskk->top;

		if (bskk->top == NULL) return bskk;
		else{
			if (bskk->bottom == bskk->top)
			{
				res = *p;
				delete p;
				bskk->bottom = bskk->top = NULL;
				return bskk;
			}
		}

		res = *p;

		bskk->top = p->pnext;
		delete p;
		return bskk;
	}

}
