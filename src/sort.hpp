#include<stdio.h>
#include<iostream>
#include<stdlib.h>

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void print(int num[], int size) {
    for (int i = 0; i<size; i++){
        printf("%d ", num[i]);
    }
    printf("\n");
}
///stability: equal data's order do not reverse after sort
///@note: not a always winner in sort algorithm

/// bubble_sort
///一趟排序： 从上到下，每两个比较，大的换到下面
///第一趟N个，然后最大的在最下面
///第二趟N-1个， 其中最大的在最下面的上面一个
///...
///最好情况：顺序：T=O(N)
///只走一遍#1循环(j=size-1), 进入#2循环一次后就break(比较N-1次)

///最坏情况：逆序：T=O(N^2)
///内外循环都会走完(最大的会依次往下挪挪到最下面)

///适合链表
///稳定性
void bubble_sort(int num[], int size) {
    for (int j = size - 1; j >= 0; j--) { //#1
        bool flag = false;
        for (int i = 0; i < j; i++) { //one pass start //#2
            if (num[i] > num[i + 1]) {
                swap(num[i], num[i + 1]);
                flag = true; //there are swap
            }
        } //one pass end
        if (!flag) break; //if there are no swap, mean it is ordered
    }
}

/// insert_sort
///先把第一个放到一边，然后把剩余的依次插入，大的放到最后
///每插入一个数，只要比最后的数小，则往前移(其他数往后)

///最好情况： T=O(N)，只需得到所有数一遍，不会进入内循环
///最坏情况： T=O(N^2)，所有的牌都向后移动

///稳定性
///如果序列基本有序，则插入排序简单高效
///T(N,I)=O(N+I) I：逆序对个数
void insert_sort(int num[], int size) {
    for (int i = 1; i < size; i++) {
        int tmp = num[i];//get a new one
        int j;
        for (j = i; j>0 && num[j - 1] > tmp; j--) {
            num[j] = num[j - 1];//move to new position to make a place for new one
        }
        num[j] = tmp;//new one located
    }
}

///逆序对： 下标i<j, A[i]>A[j]
///定理： 任意N个不同元素组成的序列平均具有N(N-1)/4个逆序对
///定理： 任何仅以交换相邻元素来排序的算法的平均时间复杂度是Ω(N^2)
///Ω:下界，O:上界，θ：上下界
///思路：1.每次消去不止1个逆序对，2.每次交换相隔较远的元素

///shell sort
///定义增量序列D[m] > D[m-1]>...>D[1]=1
///对每个D[k]进行 D[k]间隔 简单排序(bubble或insert)
///前一次间隔排序在执行新的一次间隔排序后依然有序

///origin shell sort: D[m] = floor(N/2),D[k]=floor(D[k+1]/2)
///最坏情况： T=θ(N^2),几乎就是N^2的复杂度
///增量元素不互质，小的可能无用
void shell_sort(int num[], int size) {
    for(int D = size/2; D>0; D /= 2) {
        for(int i=D; i< size; i++) { //interval D
            int tmp = num[i];//pick a num
            int j;
            for(j = i; j>=D && num[j-D] > tmp; j -= D)
                num[j] = num[j-D];//mv big one to right
            num[j] = tmp;//set the num
        }
    }
}
///Hibbard增量序列
///D[k] = 2^k -1  相邻元素互质
///最坏情况： T=θ(N^(3/2))
///Sedgewick增量序列
///{1,5,19,41,109,...}
///9*4^i -9*2^i+1 or 4^i -3*2^i+1

int scanMin(int num[], int i, int j) {
    int min_idx = i;
    for(int k=i+1; k<=j; k++) {
        if(num[k] < num[min_idx])
            min_idx = k;
    }
    return min_idx;
}

///select sort
///先找最小，与第0个交换，第0个最小
///然后从第一个开始找最小，与第一个交换，第1个第二小
///交换部分：O(N)
///找最小：O(N)
///总：T=θ(N^2)
void select_sort(int num[],int size) {
    for(int i = 0; i < size; i++) {
        int min_pos = scanMin(num, i, size-1);
        swap(num[i], num[min_pos]);
    }
}

///heap sort O(N*logN)
void heap_sort(int num[], int size) {
    //build max heap  O(N)
    for (int child = size; child > 0; child--){
        int parent = child / 2;
        if (parent == 0) break;

        if ( num[parent-1] < num[child-1]){
            int tmp = num[child-1];
            num[child-1] = num[parent-1];
            num[parent-1] = tmp;
        }
    }
    ///put max one to last, and rebuild max heap O(N*logN)
    for (int i = size; i > 0; i--){
        int maxxx = num[0];
        int j = 1;
        int child = 1;
        int last = num[i-1];
        for (; j * 2 <= i; j = child)
        {
            child = 2 * j;
            if (child != i /*this mean child+1 also <= H->size*/ \
                && (num[child-1] < num[child]))
            {
                child++; // if right bigger than left
            }

            if (last >= num[child-1]) break; //last one bigger than left and right child
            else
                num[j-1] = num[child-1];
        }
        num[i - 1] = maxxx;
    }
}

///归并  O(N)
///待归并元素都放到num中，第一个数组从索引L开始
///第一个数组结束后紧接着第二个数组从索引R开始
///在索引RightEnd结束
void merge(int num[],int tmpA[], int L, int R, int RightEnd){
    int LeftEnd = R-1;
    int tmp = L;
    int numElements = RightEnd - L + 1;
    while(L <= LeftEnd && R<= RightEnd) {
        if(num[L] <= num[R])
            tmpA[tmp++] = num[L++];
        else
            tmpA[tmp++] = num[R++];
    }

    while(L <= LeftEnd) tmpA[tmp++] = num[L++];

    while(R <= RightEnd) tmpA[tmp++] = num[R++];

    for(int i =0;i<numElements;i++,RightEnd--)
        num[RightEnd]=tmpA[RightEnd];
}

///分而治之
///递归
///      L             |              RightEnd
///num[]:0 1 2 3 4 5 6 .........n-3 n-2 n-1

///           T(N/2)        T(N/2)
///                    O(N)合并

///T(N) = T(N/2) + T(N/2) + O(N)
///T(N) = O(NlogN)

void msort(int num[],int tmpA[], int L, int RightEnd) {
    int center;
    if(L < RightEnd) {
        center = (L + RightEnd) / 2;
        msort(num, tmpA, L, center);
        msort(num, tmpA, center+1, RightEnd);
        merge(num, tmpA, L, center+1, RightEnd);
    }
}

///API //稳定
void merge_sort(int num[],int size) {
    int *tmpA;
    tmpA = (int*)malloc(size * sizeof(int));
    if(tmpA != NULL) {
        msort(num, tmpA, 0, size-1);
        free(tmpA);
    }
    else{
        printf("no memory\n");
    }
}

///非递归, 额外空间复杂度O(N)
/// num[]: 0 1 2 3 ..............n-4 n-3 n-2 n-1
///         *   *                   *       *
///           *                         *
///                         *

void merge01(int num[], int tmpA[], int L, int R, int RightEnd) {
    int LeftEnd = R-1;
    int tmp = L;
    int numElements = RightEnd - L + 1;
    while(L <= LeftEnd && R<= RightEnd) {
        if(num[L] <= num[R])
            tmpA[tmp++] = num[L++];
        else
            tmpA[tmp++] = num[R++];
    }

    while(L <= LeftEnd) tmpA[tmp++] = num[L++];

    while(R <= RightEnd) tmpA[tmp++] = num[R++];
}

void merge_pass(int num[], int tmpA[], int N, int length/*当前有序子列长度*/) {
    int i;
    for(i=0; i<= N-2*length;i+= 2*length)
        merge01(num, tmpA, i, i+length, i+2*length-1);
    if(i+length < N) //有尾巴, 归并最后两个子列
        merge01(num, tmpA, i, i+length, N-1);
    else
        for(int j=i;j<N;j++) tmpA[j] = num[j];
}

///API //稳定
void merge_sort01(int num[],int size) {
    int *tmpA;
    int length = 1;
    tmpA = (int*)malloc(size * sizeof(int));
    if(tmpA != NULL) {
        while(length < size){
            merge_pass(num, tmpA, size, length);
            length *= 2;
            merge_pass(tmpA, num, size, length);
            length *= 2;
        }
        free(tmpA);
    }
    else{
        printf("no memory\n");
    }
}

///快速排序 分而治之
///选主元，分于两块；两块之中再选主元，再分于两块；递归而下
///最好情况： 每次正好中分， T(N) = O(NlogN)

int median3(int num[], int left, int right)
{
  int center = (left+right)/2;
  if(num[left]> num[center])
      swap(num[left],num[center]);
  if(num[left]> num[right])
      swap(num[left],num[right]);
  if(num[center]> num[right])
      swap(num[center],num[right]);
  //at now, num[left] < num[center] < num[right]
  swap(num[center],num[right-1]);//将主元藏到右边
  //只需考虑num[left+1]...num[right-2]
  return num[right-1];
}

void quick_pass(int num[], int start, int end)
{
    //if size is too small, this algorithm is not suitable
    //one pass
    if(end - start == 0) return;
    if(end - start == 1){
        if(num[end] < num[start]) swap(num[end],num[start]);
        return;
    }
    int pivot = median3(num,start,end);
    if(end - start == 2) return;

    int i=start+1;
    int j=end-2;
    while(i < j){
        while(num[i]<pivot) i++;
        while(num[j]>pivot) j--;
        if(i<j) swap(num[i],num[j]);
    }
    swap(num[i],num[end-1]);
    quick_pass(num, start, i-1);
    quick_pass(num, i+1, end);
}

void quick_sort(int num[], int size)
{
    quick_pass(num, 0, size-1);
}

////table sort 表排序: indrectly sort 间接排序
//the sorted objects are a big struct
//do not move object itself, just move the pointer(or index) of them
//假设 A[] 是一个存放复杂结构的数组
//新建table[] 来为 A[]中的元素排序(按照某种关键字或是其他指标)
//table[] 初始化时为 0 1 2 3 4 ... N-1
//排完序后 A[] not change
//table[] 中存放排序后索引
//若要 A[] 按顺序输出
//则 A[table[0]], A[table[1]], ......., A[table[N-1]]


////physics sort 物理排序（在表排序的基础上硬要在物理内存上也有序）
//N个数字的排列由若干个独立的环组成
//一堆数字排序，最后总能形成交换的圈子，在每个圈子内交换完就完成排序
//最坏情况：有 floor(N/2)个环，每个环有两个元素；此时需要floor(3N/2)次元素移动
//T(N) = O(mN)  (如果复制时间m不可忽略)


////bucket sort 桶排序
//已知数字分布情况，如：       0 1 2 3 4 .....88....100
//int* count[]存放符合指针头：# # # # #......#......#
//指针头形成链表存放对应符合数字的元素
//T(N,M) = O(M+N)
//N表示要插入N次
//M表示数字分布的种类个数，因为在最后需要进行M次的遍历来输出或赋值形成有序数列


////基数排序 : 如果桶排序中 M 远大于 N
//例如，先个位，再十位，接着更高位的桶排序(次位优先)
//T=O(P*(N+B))
//B:桶的个数
//P:pass，趟数


////多关键字排序
//可以次位优先桶排序： 例如扑克牌先为面值建立13个桶
//再为花色建立4个桶
