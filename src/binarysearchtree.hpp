#include<stdio.h>
#include<iostream>

///回顾
///普通线性查找，T=O(N)
///二分查找，T=O(log2N)

///binary search tree
///左子树所有的值 < 根节点的值
///右子树所有的值 > 根节点的值
///递归的，左右子树都是 二叉搜索树

//implement
///InRec 递归
#include"bintree_common.h"

namespace bbt{

    node* findInSearchTreeInRec(node* root, int x)
    {
        if (!root) return NULL;
        if (x > root->val)
            return findInSearchTreeInRec(root->pright, x);
        else if (x < root->val)
            return findInSearchTreeInRec(root->pleft, x);
        else
            return root;
    }

    node* findInSearchTree(node* root, int x)
    {
        while (root){
            if (x < root->val)
                root = root->pleft;
            else if (x>root->val)
                root = root->pright;
            else
                return root;
        }
        return NULL;

    }

    node* findMinInSearchTree(node* root)
    {
        if (!root) return NULL;
        while (root->pleft)
            root = root->pleft;
        return root;
    }

    node* findMaxInSearchTree(node* root)
    {
        if (root)
            while (root->pright) root = root->pright;
        return root;
    }

    node* findMinInSearchTreeInRec(node* root)
    {
        if (!root)
            return NULL;
        else if (!root->pleft)
            return root;
        else
            return findMinInSearchTreeInRec(root->pleft);

    }

    node* findMaxInSearchTreeInRec(node* root)
    {
        if (!root)
            return NULL;
        else if (!root->pright)
            return root;
        else
            return findMinInSearchTreeInRec(root->pright);

    }


    node* insertSearchTree(node* root, int x)
    {
        if (root == NULL){
            root = new node;
            root->val = x;
        }
        else{
            if (x < root->val){
                root->pleft = insertSearchTree(root->pleft, x);
            }
            else {
                root->pright = insertSearchTree(root->pright, x);
            }
        }
        return root;
    }

    node* deleteInSearchTree(node* root, int x)
    {
        node* tmp = 0;
        if (!root)
            printf("no X found!\n");
        else if (x < root->val)
            root->pleft = deleteInSearchTree(root->pleft, x);
        else if (x > root->val)
            root->pright = deleteInSearchTree(root->pright, x);
        else { //found the value
            if (root->pleft && root->pright) //have both
            {
                tmp = findMinInSearchTree(root->pright);
                //min of right is bigger than all left node
                //and is smaller than all other right node
                root->val = tmp->val;
                root->pright = deleteInSearchTree(root->pright, root->val);
            }
            else
            {
                tmp = root;
                if (!root->pleft)
                    root = root->pright;
                else if (!root->pright)
                    root = root->pleft;
                delete tmp;
            }
        }
        return root;
    }
}

