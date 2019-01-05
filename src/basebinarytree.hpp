#include<iostream>

//using for general list
#include<string>

//using for no recursive traverse
#include<stack>

//using for level traverse
#include<queue>

#include"bintree_common.h"

using namespace std;

namespace bbt{

	const int max_size = 10000;

	node* create(int nums[], int n, int& i)
	{
		node* p = NULL;
		if (i < n)
		{
			int value = nums[i];
			i++;

			if (value != -9999)
			{
				p = new node;
				p->val = value;
				p->pleft = create(nums, n, i);
				p->pright = create(nums, n, i);
			}
		}
		return p;
	}

	node* init(int nums[], int n)
	{
		int i=0;
		node* root = create(nums, n, i);
		return root;
	}

	/*��txt�ж�ȡ���ݣ�����һ������
	���ݹ������£�
	1.Ԫ��֮���Կո����
	2.����˳��Ĭ��Ϊ�������(��������)
	3.-9999����ǰ�ڵ��������û��Ԫ���ˣ�ת������
	4.�Ѿ�ת�����������Գ���-9999��
	  ��ת����ǰ�ڵ�ĸ��ڵ�����������Դ����ơ�
	5.����:
	  TXT���ݣ�
	    1 2 3 -9999 -9999 4 -9999 -9999 5 6 -9999 -9999 7
	  ���ɵ������£�
	              1
				  /\
				 /  \
				/    \
			   /      \
			  /        \
			 2          5
			/ \        / \
		   3   4      6   7
		  /\   /\    /\   
		 #  # #  #  #  # 
	*/

	//��ʼ��������������������Ȼ������ʼ������
	/*
	int number[max_size];
	int num;
	int ct = 0;
	while (cin >> num)
	{
		number[ct] = num;
		++ct;

		if (cin.get() == '\n')break;
	}

	int len = ct;

	for (int i = 0; i < len; i++)
	{
		cout << number[i] << " ";
	} cout << endl;

	node* root_ = init(number, len);
	*/
	//��ʼ��������������������Ȼ������ʼ������



	//���ļ�����
	/*
	int number[max_size];
	int num;
	int ct = 0;

	string data = "D:\\Program Files\\Projects\\datastruct\\Debug\\data.txt";
	ifstream input(data);

	while (input >> num)
	{
		number[ct] = num;
		++ct;
	}

	int len = ct;

	for (int i = 0; i < len; i++)
	{
	cout << number[i] << " ";
	} cout << endl;

	node* root_ = init(number, len);
	*/
	//���ļ�����

	//�������
	void preorder(node* root)
	{
		if (root == NULL)
			cout << "# ";
		else{
			cout << root->val<<" ";
			preorder(root->pleft);
			preorder(root->pright);
		}
	}


	//�������
	void inorder(node* root)
	{
		if (root == NULL)
			cout << "# ";
		else{
			inorder(root->pleft);
			cout << root->val << " ";
			inorder(root->pright);
		}
	}


	//�������
	void postorder(node* root)
	{
		if (root == NULL)
			cout << "# ";
		else{
			postorder(root->pleft);
			postorder(root->pright);
			cout << root->val << " ";
		}
	}

	//�ڵ���
	void numofnode(node* root, int& num)
	{
		if (root != NULL)
		{
			num++;
			numofnode(root->pleft, num);
			numofnode(root->pright, num);
		}
	}
	
	//���ؽڵ���
	int nodecount(node* root)
	{
		if(root==NULL) return 0;
		else return 1 + nodecount(root->pleft) + nodecount(root->pright);
	}
	
	//Ҷ����
	void numofleaf(node* root, int& num)
	{
		if (root != NULL){
			if ((root->pleft == NULL) && (root->pright == NULL))
			{
				cout << "\nleaf value: " << root->val;
				num++;
			}

			numofleaf(root->pleft, num);
			numofleaf(root->pright, num);
		}
	}
    
	//����Ҷ����
	int numofleaf(node* root)
	{
		if(root==NULL)
			return 0;
		else if((root->pleft == NULL) && (root->pright == NULL))
		return 1;
		return numofleaf(root->pleft) + numofleaf(root->pright);
	}
	
	//���
	void depthoftree(node* root, int k, int& h)
	{
		if (root != NULL)
		{
			k++;
			if (k > h)
				h = k;

			depthoftree(root->pleft, k, h);
			depthoftree(root->pright, k, h);
		}
	}

	//�������
	int depthoftree1(node* root)
	{
		if(root==NULL)
			return 0;
		else{
			int dep1 = depthoftree1(root->pleft);
			int dep2 = depthoftree1(root->pright);
			return dep1>dep2 ? (dep1+1) : (dep2+1);
		}
		
	}
	
	//�Ƿ��ض�ֵ
	bool isContain(node* root, int value)
	{
		if (root != NULL){
			if (root->val == value)
				return true;

			if (isContain(root->pleft, value) || isContain(root->pright, value))
				return true;
		}
		else return false;
	}

	//����ĳֵ�ĸ���
	void numOfContain(node* root, int value, int& res)
	{
		if (root != NULL){
			if (root->val == value)
			{
				res++;
			}
			numOfContain(root->pleft, value, res);
			numOfContain(root->pright, value, res);
		}
	}
	
	//����ĳֵ�ĸ���
	int numOfContain(node* root, int value)
	{
		if (root == NULL) return 0;
		else if (root->val == value)
			return 1 + numOfContain(root->pleft, value) + numOfContain(root->pright, value);
		else
		return numOfContain(root->pleft, value) + numOfContain(root->pright, value);
	}

	//�����µĸ��ڵ㣬��ԭ�ȵ�����Ϊ�����������
	node* insertNewRoot(node* root, int value, bool left)
	{
		node* newroot = NULL;
		newroot = new node;
		newroot->val = value;
		if (left)
		{
			newroot->pleft = root;
		}
		else{
			newroot->pright = root;
		}
		return newroot;
	}

	//�����½ڵ�
	void insertNode(node* parent, int value, bool left)
	{
		node* tp = new node;
		tp->val = value;
		if (left)
		{
			tp->pleft = parent->pleft;
			parent->pleft = tp;
		}
		else{
			tp->pright = parent->pright;
			parent->pright = tp;
		}
	}

	//�ڿ�ָ���������һ����
	void insertAnotherTree(node* parent, node* ano_root, bool left)
	{
		if ( left&&(parent->pleft != NULL) || (!left)&&(parent->pright != NULL))
		{
			cout << "no empty points in inserting area!" <<endl;
			return;
		}

		if (left)
		{
			parent->pleft = ano_root;
		}
		else{
			parent->pright = ano_root;
		}
	}

	//��ֵΪtarget�Ľڵ�������Ҳ����½ڵ�
	void insertByVal(node* root, int target, int value, bool left)
	{
		if (root != NULL)
		{
			if (root->val == target)
				insertNode(root, value, left);

			insertByVal(root->pleft, target, value, left);
			insertByVal(root->pright, target, value, left);
		}
	}
	
	//�ݹ�ɾ������
	void delSubTreeRe(node* parent)
	{
		if (parent != NULL)
		{
			delSubTreeRe(parent->pleft);
			delSubTreeRe(parent->pright);
			delete parent;
		}
	}

	//ɾ����parentΪ���ڵ������
	void delSubTree(node*& parent)
	{
		delSubTreeRe(parent);
		parent = NULL;
	}

	//ɾ���ڵ����������������
	void delSideSubTree(node* parent, bool left)
	{
		if(parent != NULL)
		{
			if (left)
			{
				delSubTree(parent->pleft);
			}
			else{
				delSubTree(parent->pright);
			}
		}
	}

	//������ӡ��
	void inGenList(node* root)
	{
		if (root == NULL) cout << "#";
		else{
			cout << root->val;
			if (root->pleft != NULL || root->pright != NULL)
			{
				cout << "(";
				inGenList(root->pleft);
				cout << ",";
				inGenList(root->pright);
				cout << ")";
			}
		}
	}
	
	//�ݹ�ӹ����������i��ʼ��Ϊ0��
	node* create(string& genl, int& i)
	{
		if (genl[i] == '#')
		{
			i++; return NULL;
		}

		int n = 0;
		char ch;
		while (i < genl.size() && (ch = genl[i + n]) && ch != '(' && ch != ',' && ch != ')')
			n++;

		string str = genl.substr(i, n);
		i += n;

		node* p = new node;
		p->val = atoi(str.c_str());

		if (genl[i] == '(')
		{
			i++;
			p->pleft = create(genl, i);
			i++;
			p->pright = create(genl, i);
			i++;
		}
		return p;
	}

	//�ǵݹ��������
	//----���ڵ��������ߣ�����ֵ�ʹ�ӡ������ӡ��������ջ��ֱ������ĳ�ڵ�X��������Ϊ�գ���ʱջ��ΪX���˳���whileѭ��
	//----����if��䣬X��ջ��ָ��p��ΪX������������ӡ����������������ָ��ִ��if����еĳ�ջ��X��parent����������������
	//----����ѭ�����ݵ����ڵ㣬����root��������
	void preorderNoRe(node* root)
	{
		if (!root) return;
		stack<node*> st;
		node* p = root;
		while (p || !st.empty())
		{
			while (p)
			{
				cout << p->val << " ";
				st.push(p);
				p = p->pleft;
			}

			if (!st.empty())
			{
				p = st.top();
				st.pop();
				p = p->pright;
			}
		}
		cout << endl;
	}

	//�ǵݹ�������� 
	//----���ڵ��������ߣ���ֵ����ջ��ֱ������ĳ�ڵ�X��������Ϊ�գ���ʱջ��ΪX����X��ջ����ӡX������X��������
	//----X��������������󣬻����ڿ�ָ��p�Ӷ�����else��䣬X��parent�ڵ��ջ����ӡparent�ڵ㣬һֱ���ϻ���
	//----���ݵ����ڵ㣬��ӡroot������root��������
	void inorderNoRe(node* root)
	{
		stack<node*> st;
		node* p = root;
		while (p || !st.empty()){
			if (p) {
				st.push(p);
				p = p->pleft;
			}
			else{
				p = st.top();
				st.pop();
				cout << p->val << " ";
				p = p->pright;
			}
		}
		cout << endl;
	}

	//����ǵݹ����
	//----���ڵ��������ߣ���ֵ����ջ��ֱ������ĳ�ڵ�X��������Ϊ�գ���ʱջ��ΪX�������X������������if��䲻ִ��,ִ��else���
	//----����X��������������ͷʱp->prightΪ�գ�����������ڵ㣬pre����ΪX->pright,p����ΪNULL��Ȼ��Xλ��ջ����if�������ϣ����
	//----X�ڵ㣬p����Ϊnull��������ջֱ���ص����ڵ㣬Ȼ��ͨ��else������������
	//pre�����ã�����ӡ��root��������ʱ���������ĸ��ڵ㱻���Ϊpre�� �������Ǿ��ܽ���if��䣨����root->pright == pre����ӡ���ڵ㣬�Ӷ���֤���Ҹ���˳��
	void postorderNoRe(node* root)
	{
		stack<node*> st;
		node* p = root;
		node* pre = NULL;
		while ( p || !st.empty())
		{
			while (p)
			{
				st.push(p);
				p = p->pleft;
			}
			p = st.top();
			if (p->pright == NULL || p->pright == pre)
			{
				cout << p->val << " ";
				pre = p;
				st.pop();
				p = NULL;
			}
			else p = p->pright;	
		}
		cout << endl;
	}

    //��α���
	void levelorder(node* root)
	{
		queue<node*> qe;
		node* p = root;
		while (p)
		{
			cout << p->val << " ";
			if (p->pleft)
				qe.push(p->pleft);
			if (p->pright)
				qe.push(p->pright);

			p = qe.empty() ? NULL : qe.front();
			if (!qe.empty())
			    qe.pop();
		}
		cout << endl;
	}

	//ĳֵ���ֵĲ���(k��ʼֵΪ1��h��ʼֵΪ0���������ұ�����飩
	void layerofval_l(node* root, int k, int target, int &h)
	{
		if (root != NULL)
		{
			if (root->val == target)
			{
				h = k;
				return;
			}

			layerofval_l(root->pleft, k + 1, target, h);
			layerofval_l(root->pright, k + 1, target, h);
		}
	}
	//ĳֵ���ֵĲ���(k��ʼֵΪ1��h��ʼֵΪ0�������ҵ��������飩
	void layerofval_r(node* root, int k, int target, int &h)
	{
		if (root != NULL)
		{
			if (root->val == target)
			{
				h = k;
				return;
			}

			layerofval_r(root->pright, k + 1, target, h);
			layerofval_r(root->pleft, k + 1, target, h);
		}
	}

	//��ӽ������ֵĲ���
	int firstsee(node* root, int target)
	{
		int k1 = 1;
		int h1 = 0;
		layerofval_l(root, k1, target, h1);

		int k2 = 1;
		int h2 = 0;
		layerofval_r(root, k2, target, h2);

		return h1 > h2 ? h2 : h1;

	}


}