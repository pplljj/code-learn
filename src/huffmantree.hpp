#include<stdio.h>
#include<iostream>

///带权路径长度(WPL)
///设二叉树有n个叶子结点，每个叶子结点带有权值Wk
///从根到叶子的长度Lk
///则带权路径长度和
//      n
//WPL = ∑Wk*Lk
//      k=1

///哈夫曼树，最优树
///没有度为1的节点
///n个叶子节点的哈夫曼树共2n-1个结点
///任意非叶结点的左右子树交换仍是哈夫曼树
///不同构（同一份数据构造但是顺序不同）的哈夫曼树有相同的WPL

//构造一颗哈夫曼树

#include "binaryheap.hpp"

///first we should use MinHeap_t* buildMinHeap(int num[], int size)
///to build a min heap as the param in of Huffman function

///O(Nlog2N)
HuffmanNode* Huffman(MinHeap_t* H)
{
    int i;
    HuffmanNode* T;
    int size = H->size;
    for (i = 1; i < size/*H->size*/; i++){ //size-1 times
        T = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
        T->left = minHeapPop(H);
        T->right = minHeapPop(H);
        T->weight = T->left->weight + T->right->weight;

        minHeapInsert(H, *T);
    }
    T = minHeapPop(H);
    return T;
}

///哈夫曼编码
////前缀编码

///左分支： 0 ； 右分支： 1
///字符只在叶子结点上

///根据频率排序
///找最小的两个合并

