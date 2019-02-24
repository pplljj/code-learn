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

    //定义的树的数据存在txt中
    const char* data = "../data/tree.txt";
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

    /*从txt中读取数据，生成一个树。
    数据规则如下：
    1.元素之间以空格隔开
    2.数据顺序默认为先序遍历(根、左、右)
    3.-9999代表当前节点的左子树没有元素了，转右子树
    4.已经转到右子树，仍出现-9999，
      则转往当前节点的父节点的右子树。以此类推。
    5.例子:
      TXT数据：
        1 2 3 -9999 -9999 4 -9999 -9999 5 6 -9999 -9999 7
      生成的树如下：
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

    int ao = numOfContain(root_, 7);
    cout << "there are " << ao  << "ge 7" << endl;

    int yu = nodecount(root_);
    cout << "node num: "<<yu << endl;

    int nodenum = 0;
    numofnode(root_, nodenum);
    cout << "nodes number: " << nodenum<<endl;

    node* _root = insertNewRoot(root_, 657, false);
    preorder(_root); cout << endl;
    inorder(_root); cout << endl;
    postorder(_root); cout << endl;

    int yhn = firstsee(root_, 4);
    cout << "4 is first saw at " << yhn << " th layer"<< endl;


    insertNode(_root->pright, 1024, true);
    preorder(_root); cout << endl;
    inorder(_root); cout << endl;
    postorder(_root); cout << endl;
#if 0
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
