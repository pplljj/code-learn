#include<stdio.h>
#include<iostream>
#include<stdlib.h>

//完全二叉树就是满二叉树缺最后的一些元素
//编号从1开始，共N个结点，则数组大小 N+1
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

   根节点： 1

   非根结点i的父结点是 floor(i/2)
   例如：M索引为6，floor(3)=3,父结点为3；Q为7，floor(3.5)=3,父结点为3

   结点i的左孩子的结点索引是2i
   例如：O为3，则M为6；2i<=N,  否则没有左孩子

   结点i的右孩子的结点索引是2i+1
   2i+1<=N, 否则没有右孩子
*/


//优先队列：优先权（关键字优先）
//最大的在树根---最大堆，与之对应的最小堆
//堆：完全二叉树，可用数组表示
//根节点的值 全部大于(或小于) 左右子树的结点的值

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

//教学视频实现
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

//给N个元素建立最大堆
//1.通过插入操作，一个个相继插入，复杂度为O(N*logN)
//2.线性时间复杂度
////2.1按输入顺序存入，满足完全二叉树的结构特征
////2.2调整各个节点位置，以满足最大堆的有序特性

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

//教学视频实现
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

//给N个元素建立最大堆
//1.通过插入操作，一个个相继插入，复杂度为O(N*logN)
//2.线性时间复杂度
////2.1按输入顺序存入，满足完全二叉树的结构特征
////2.2调整各个节点位置，以满足最大堆的有序特性

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