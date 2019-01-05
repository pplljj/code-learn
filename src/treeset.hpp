#include<stdio.h>
#include<iostream>

#define PARENT_FLAG -1
#define MAX_SET_SIZE 100
////���ϣ� ����ÿ��������һ������Ԫ��

typedef struct{
	int data;
	int parent;
}Set_t;

///����һ�����飬data�򴢴�ֵ,parent�򴢴游�����ڼ���ͷ���

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

///����
int FindInSet(Set_t S[], int x)
{
	int i;
	for (i = 0; i < MAX_SET_SIZE && S[i].data != x; i++); //�ҵ�x��Ӧ��data���±�
	if (i >= MAX_SET_SIZE) return -1;
	for (; S[i].parent >= 0; i = S[i].parent);//ֱ���ҵ�parent = -1��һ�����ߵ������
	return i; //����parent�����ڵ㣩�������е�����
}

///���ϵĲ�����

///�ҵ�����Ԫ�����ڼ��ϵĸ��ڵ�
///�����ͬ����������һ�����ڵ�ĸ����ָ�����ó���һ�����ڵ�������±�

void UnionSet(Set_t S[], int x1, int x2)
{
	int root1 = FindInSet(S, x1);
	int root2 = FindInSet(S, x2);
	if (root1 != root2) S[root2].parent = root1;
}

///����С�ļ��Ϻϲ�����Դ�ļ��������Ʋ�������
///��������parent��ľ���ֵ��Ϊ�������ڵ�ĸ���