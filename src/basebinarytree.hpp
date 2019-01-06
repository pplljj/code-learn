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

    //初始化二叉树（输入多个数字然后换行则开始构建）
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
    //初始化二叉树（输入多个数字然后换行则开始构建）



    //从文件构建
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
    //从文件构建

    //先序遍历
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


    //中序遍历
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


    //后序遍历
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

    //节点数
    void numofnode(node* root, int& num)
    {
        if (root != NULL)
        {
            num++;
            numofnode(root->pleft, num);
            numofnode(root->pright, num);
        }
    }
    
    //返回节点数
    int nodecount(node* root)
    {
        if(root==NULL) return 0;
        else return 1 + nodecount(root->pleft) + nodecount(root->pright);
    }
    
    //叶子数
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
    
    //返回叶子数
    int numofleaf(node* root)
    {
        if(root==NULL)
            return 0;
        else if((root->pleft == NULL) && (root->pright == NULL))
        return 1;
        return numofleaf(root->pleft) + numofleaf(root->pright);
    }
    
    //深度
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

    //返回深度
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
    
    //是否含特定值
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

    //含有某值的个数
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
    
    //返回某值的个数
    int numOfContain(node* root, int value)
    {
        if (root == NULL) return 0;
        else if (root->val == value)
            return 1 + numOfContain(root->pleft, value) + numOfContain(root->pright, value);
        else
        return numOfContain(root->pleft, value) + numOfContain(root->pright, value);
    }

    //插入新的根节点，把原先的树作为左或者右子树
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

    //插入新节点
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

    //在空指针域插入另一颗树
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

    //在值为target的节点左或者右插入新节点
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
    
    //递归删除子树
    void delSubTreeRe(node* parent)
    {
        if (parent != NULL)
        {
            delSubTreeRe(parent->pleft);
            delSubTreeRe(parent->pright);
            delete parent;
        }
    }

    //删除以parent为根节点的子树
    void delSubTree(node*& parent)
    {
        delSubTreeRe(parent);
        parent = NULL;
    }

    //删除节点的左子树或右子树
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

    //广义表打印树
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
    
    //递归从广义表构建树（i初始化为0）
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

    //非递归先序遍历
    //----根节点起往左走，遇到值就打印（即打印根）并入栈，直到遇到某节点X的左子树为空，此时栈顶为X，退出内while循环
    //----进入if语句，X出栈，指针p置为X的右子树，打印完右子树，遇到空指针执行if语句中的出栈将X的parent弹出，进入右子树
    //----依次循环回溯到根节点，进入root的右子树
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

    //非递归中序遍历 
    //----根节点起往左走，有值就入栈，直到遇到某节点X的左子树为空（此时栈顶为X），X出栈，打印X，访问X的右子树
    //----X的右子树访问完后，会由于空指针p从而进入else语句，X的parent节点出栈，打印parent节点，一直往上回溯
    //----回溯到根节点，打印root，访问root的右子树
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

    //后序非递归遍历
    //----根节点起往左走，有值就入栈，直到遇到某节点X的左子树为空（此时栈顶为X），如果X有右子树，则if语句不执行,执行else语句
    //----进入X的右子树，到尽头时p->pright为空，输出右子树节点，pre被置为X->pright,p被置为NULL；然后X位于栈顶，if条件符合，输出
    //----X节点，p被置为null，继续出栈直到回到根节点，然后通过else语句进入右子树
    //pre的作用：当打印完root的右子树时，右子树的根节点被标记为pre， 这样我们就能进入if语句（满足root->pright == pre）打印根节点，从而保证左右根的顺序
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

    //层次遍历
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

    //某值出现的层数(k初始值为1，h初始值为0）（从左到右遍历检查）
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
    //某值出现的层数(k初始值为1，h初始值为0）（从右到左遍历检查）
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

    //最接近根出现的层数
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
