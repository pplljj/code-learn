#include<stdio.h>
#include<iostream>
#include<stdlib.h>

//��ȫ������������������ȱ����һЩԪ��
//��Ŵ�1��ʼ����N����㣬�������С N+1
/*
                A
			  /	  \
            B       O
		  /  \     /  \
         C    S   M    Q
	    / \
	  W    K

	node: A B O C S M Q W K
   index: 1 2 3 4 5 6 7 8 9

   ���ڵ㣺 1

   �Ǹ����i�ĸ������ floor(i/2)
   ���磺M����Ϊ6��floor(3)=3,�����Ϊ3��QΪ7��floor(3.5)=3,�����Ϊ3

   ���i�����ӵĽ��������2i
   ���磺OΪ3����MΪ6��2i<=N,  ����û������

   ���i���Һ��ӵĽ��������2i+1
   2i+1<=N, ����û���Һ���
*/


//���ȶ��У�����Ȩ���ؼ������ȣ�
//����������---���ѣ���֮��Ӧ����С��
//�ѣ���ȫ�����������������ʾ
//���ڵ��ֵ ȫ������(��С��) ���������Ľ���ֵ

#define MAX_DATA 999999

typedef struct Heap_ {
	int *elements; //a point to an array
	int size; //num of element
	int capacity; //max capacity
} MaxHeap_t;

int isHeapFull(MaxHeap_t* H)
{
	if (H->size < H->capacity)
		return 0;
	else return 1;
}

MaxHeap_t* heapCreate(int maxSize)
{
	MaxHeap_t* H = (MaxHeap_t*)calloc(1, sizeof(MaxHeap_t));
	H->elements = (int*)calloc(maxSize + 1, sizeof(int));
	H->size = 0;
	H->capacity = maxSize;
	H->elements[0] = MAX_DATA;
	return H;
}


/// T(N) = O(log2N)
void heapInsert(MaxHeap_t* H, int data)
{
	int i;
	if (isHeapFull(H)){
		printf("heap is full.\n");
		return;
	}

	i = ++H->size; //last element after insert

	for (; H->elements[i / 2] < data; i /= 2) //if parent node is smaller than data
		H->elements[i] = H->elements[i / 2];  //move parent val down
	                                          //i/2 finally become 0, is the max data, condition break;
	H->elements[i] = data;
}

/// T(N) = O(log2N)
int heapPop(MaxHeap_t* H)
{
	int pop_val = H->elements[1];
	int i = H->size--;
	int last = H->elements[i];
	int j = 1;
	for (; 2 * j + 1 <= H->size && (H->elements[2 * j] > last || H->elements[2 * j + 1] > last);)
	{
		H->elements[j] = (H->elements[2 * j] > H->elements[2 * j + 1] ? H->elements[2 * j] : H->elements[2 * j + 1]);
		j = (H->elements[2 * j] > H->elements[2 * j + 1] ? (2 * j) : (2 * j + 1));
	}
	if (2 * j == H->size && H->elements[2 * j] > last) //at bottom have left but no right
	{
		H->elements[j] = H->elements[2 * j];
		j *= 2;
	}
	H->elements[j] = last;
	return pop_val;
}

//��ѧ��Ƶʵ��
int heapPopVideo(MaxHeap_t* H)
{
	int pop_val = H->elements[1];
	int last = H->elements[H->size--];
	int j = 1;
	int child = 1;
	for (; j * 2 <= H->size; j = child)
	{
		child = 2 * j;
		if (child != H->size /*this mean child+1 also <= H->size*/ \
			 && (H->elements[child] < H->elements[child + 1]))
		{
			child++; // if right bigger than left
		}

		if (last >= H->elements[child]) break; //last one bigger than left and right child
		else
			H->elements[j] = H->elements[child];
	}
	H->elements[j] = last;
	return pop_val;
}

//��N��Ԫ�ؽ�������
//1.ͨ�����������һ������̲��룬���Ӷ�ΪO(N*logN)
//2.����ʱ�临�Ӷ�
////2.1������˳����룬������ȫ�������Ľṹ����
////2.2���������ڵ�λ�ã����������ѵ���������

MaxHeap_t* buildHeap(int num[], int size)
{
	MaxHeap_t * H = heapCreate(size);
	for (int i = 0; i < size; i++)
		H->elements[i + 1] = num[i];
	H->size = size;

	for (int child = H->size; child > 0; child--){
		int parent = child / 2;
		if (parent == 0) break;

		if (H->elements[parent] < H->elements[child]){
			int tmp = H->elements[child];
			H->elements[child] = H->elements[parent];
			H->elements[parent] = tmp;
		}
	}
}

//*************min heap for huffman*******************//

#define MIN_DATA -999999

typedef struct HuffmanNode{
	int weight;
	struct HuffmanNode *left, *right;
}HuffmanNode;

typedef struct Min_Heap {
	HuffmanNode *elements; //a point to an array
	int size; //num of element
	int capacity; //max capacity
}MinHeap_t;

int isMinHeapFull(MinHeap_t* H)
{
	if (H->size < H->capacity)
		return 0;
	else return 1;
}


MinHeap_t* minHeapCreate(int maxSize)
{
	MinHeap_t* H = (MinHeap_t*)calloc(1, sizeof(MinHeap_t));
	H->elements = (HuffmanNode*)calloc(maxSize + 1, sizeof(HuffmanNode));

	H->size = 0;
	H->capacity = maxSize;
	H->elements[0].weight = MIN_DATA;
	return H;
}


/// T(N) = O(log2N)
void minHeapInsert(MinHeap_t* H, HuffmanNode data)
{
	int i;
	if (isMinHeapFull(H)){
		printf("heap is full.\n");
		return;
	}

	i = ++H->size; //last element after insert

	for (; H->elements[i / 2].weight > data.weight; i /= 2) //if parent node is bigger than data
	{
		H->elements[i].weight = H->elements[i / 2].weight;  //move parent val down
		H->elements[i].left  = H->elements[i / 2].left;
		H->elements[i].right = H->elements[i / 2].right;
	}
	//i/2 finally become 0, is the min data, condition break;
	H->elements[i].weight = data.weight;
	H->elements[i].left = data.left;
	H->elements[i].right = data.right;
}

/// T(N) = O(log2N)
HuffmanNode* minHeapPop(MinHeap_t* H)
{
	HuffmanNode* PT = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
	*PT = H->elements[1];

	HuffmanNode h_last = H->elements[H->size--];
	int last = h_last.weight;

	int j = 1;
	for (; 2 * j + 1 <= H->size && (H->elements[2 * j].weight < last || H->elements[2 * j + 1].weight < last);)
	{
		H->elements[j] = (H->elements[2 * j].weight < H->elements[2 * j + 1].weight ? H->elements[2 * j] : H->elements[2 * j + 1]);
		j = (H->elements[2 * j].weight < H->elements[2 * j + 1].weight ? (2 * j) : (2 * j + 1));
	}
	if (2 * j == H->size && H->elements[2 * j].weight < last) //at bottom have left but no right
	{
		H->elements[j] = H->elements[2 * j];
		j *= 2;
	}
	H->elements[j] = h_last;
	return PT;
}

//��ѧ��Ƶʵ��
HuffmanNode* minHeapPopVideo(MinHeap_t* H)
{
	HuffmanNode* PT = (HuffmanNode*)calloc(1, sizeof(HuffmanNode));
	*PT = H->elements[1];
	HuffmanNode h_last = H->elements[H->size--];
	int last = h_last.weight;
	int j = 1;
	int child = 1;
	for (; j * 2 <= H->size; j = child)
	{
		child = 2 * j;
		if (child != H->size /*this mean child+1 also <= H->size*/ \
			&& (H->elements[child].weight > H->elements[child + 1].weight))
		{
			child++; // if right smaller than left
		}

		if (last <= H->elements[child].weight) break; //last one bigger than left and right child
		else
			H->elements[j] = H->elements[child];
	}
	H->elements[j] = h_last;
	return PT;
}

//��N��Ԫ�ؽ�������
//1.ͨ�����������һ������̲��룬���Ӷ�ΪO(N*logN)
//2.����ʱ�临�Ӷ�
////2.1������˳����룬������ȫ�������Ľṹ����
////2.2���������ڵ�λ�ã����������ѵ���������

MinHeap_t* buildMinHeap(int num[], int size)
{
	MinHeap_t * H = minHeapCreate(size); //after creat, all members are null
	for (int i = 0; i < size; i++)
		H->elements[i + 1].weight = num[i];
	H->size = size;

	for (int child = H->size; child > 0; child--){
		int parent = child / 2;
		if (parent == 0) break;

		if (H->elements[parent].weight > H->elements[child].weight){
			int tmp = H->elements[child].weight;
			H->elements[child].weight = H->elements[parent].weight;
			H->elements[parent].weight = tmp;
		}
	}
}