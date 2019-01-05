#include"singledeslinks.hpp"
#include"doubledeslinks.hpp"
#include"basequeue.hpp"
#include"basestack.hpp"

#include"basebinarytree.hpp"

//for input
#include<fstream>
#include<string>


using namespace bbt;


int main()
{
	
	int number[max_size];
	int num;
	int ct = 0;
	
	//������������ݴ���txt��
	string data = "C:\\Users\\Administrator\\Desktop\\datastruct\\project\\data1.txt";
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
	node* root_ = init(number, len);

	cout << "\nxian xu" << endl;
	preorder(root_);
	
	cout << "\nzhong xu" << endl;
	inorder(root_);

	cout << "\nhou xu" << endl;
	postorder(root_);
#if 0
	int leaf = 0;
	numofleaf(root_, leaf);

	cout << "\nleaf: " << leaf << endl;


	int lf = numofleaf(root_);
	cout << lf << endl;

	int k = 0;
	int h = 0;
	depthoftree(root_, k, h);
	cout << "\ndepth: " << h << endl;

	int ol = depthoftree1(root_);
	cout << ol << endl;


	if (isContain(root_, 93))
		cout << "contain 93" << endl;

	if (isContain(root_,500))
		cout << "contain 500" << endl;

	int num_ = 0;
	numOfContain(root_, 23, num_);

	cout << "there are 23 of " << num_ << endl;

	int ao = numOfContain(root_, 23);
	cout << "OOOOOO 23 of " << ao << endl;

	int yu = nodecount(root_);
	cout << yu << endl;

	int nodenum = 0;
	numofnode(root_, nodenum);
	cout << "nodes number: " << nodenum<<endl;

	//node* _root = insertNewRoot(root_, 657, false);
	//preorder(_root); cout << endl;
	//inorder(_root); cout << endl;
	//postorder(_root); cout << endl;

	//int yhn = layerofval(root_, 93);
	//cout << "93 is at " << yhn << endl;


	//insertNode(_root->pright, 1024, true);
	//preorder(_root); cout << endl;
	//inorder(_root); cout << endl;
	//postorder(_root); cout << endl;

	//insertByVal(root_, 36, 1024, true);
	//preorder(root_); cout << endl;
	//inorder(root_); cout << endl;
	//postorder(root_); cout << endl;

	//delSubTree(root_->pright->pright);
	//preorder(root_); cout << endl;
	//inorder(root_); cout << endl;
	//postorder(root_); cout << endl;

	//inGenList(root_);

	//string gen = "23(46(36(#,93),#),36(71,#))";

	//int kk = 0;
	//node* aroot = create(gen, kk);
	//preorder(aroot); cout << endl;
	//inorder(aroot); cout << endl;
	//postorder(aroot); cout << endl;
	preorderNoRe(root_);

	inorderNoRe(root_);

	postorderNoRe(root_);

	levelorder(root_);


	
	int target = 931;
	h = firstsee(root_,target);
	cout << target << " first appear in " << h << "TH layer" <<endl;
#endif
	return 0;
}