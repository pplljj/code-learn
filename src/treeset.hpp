#include<stdio.h>
#include<iostream>

#define PARENT_FLAG -1
#define MAX_SET_SIZE 100
////集合： 树的每个结点代表一个集合元素

typedef struct{
    int data;
    int parent;
}Set_t;

///构成一个数组，data域储存值,parent域储存父亲所在集合头结点

/*

idx  data  parent
0      1     -1 //it is a parent
1      2      0 //parent's index is 0
2      3     -1
3      4      0
4      5      2 //parent's index is 2
5      6     -1
6      7      0
7      8      2
8      9      5
9      10     5

       1       3        6
      /|\      /\      /\
     2 4 7    5  8    9 10
*/

///查找
int FindInSet(Set_t S[], int x)
{
    int i;
    for (i = 0; i < MAX_SET_SIZE && S[i].data != x; i++); //找到x对应的data的下标
    if (i >= MAX_SET_SIZE) return -1;
    for (; S[i].parent >= 0; i = S[i].parent);//直到找到parent = -1，一步步走到父结点
    return i; //返回parent（根节点）在数组中的索引
}

///集合的并运算

///找到两个元素所在集合的根节点
///如果不同根，则将其中一个根节点的父结点指针设置成另一个根节点的数组下标

void UnionSet(Set_t S[], int x1, int x2)
{
    int root1 = FindInSet(S, x1);
    int root2 = FindInSet(S, x2);
    if (root1 != root2) S[root2].parent = root1;
}

///采用小的集合合并到相对大的集合来改善查找性能
///将父结点的parent域的绝对值作为集合树节点的个数
