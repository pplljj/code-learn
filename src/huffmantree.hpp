#include<stdio.h>
#include<iostream>

///��Ȩ·������(WPL)
///���������n��Ҷ�ӽ�㣬ÿ��Ҷ�ӽ�����ȨֵWk
///�Ӹ���Ҷ�ӵĳ���Lk
///���Ȩ·�����Ⱥ�
//      n 
//WPL = ��Wk*Lk
//      k=1

///����������������
///û�ж�Ϊ1�Ľڵ�
///n��Ҷ�ӽڵ�Ĺ���������2n-1�����
///�����Ҷ�������������������ǹ�������
///��ͬ����ͬһ�����ݹ��쵫��˳��ͬ���Ĺ�����������ͬ��WPL

//����һ�Ź�������

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

///����������
////ǰ׺����

///���֧�� 0 �� �ҷ�֧�� 1
///�ַ�ֻ��Ҷ�ӽ����

///����Ƶ������
///����С�������ϲ�
