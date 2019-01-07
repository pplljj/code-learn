#include<iostream>

using namespace std;

#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define INFINITY 65535

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

//邻接矩阵的好处： 直观简单好理解；方便检查任意一对顶点间是否存在边
//  方便找任一顶点的所有邻接点；方便计算任一顶点的度
//坏处： 对于稀疏图来说浪费空间和浪费时间

typedef struct
{
    VertexType vexs[MAXVEX]; /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int numNodes, numEdges; /* 图中当前的顶点数和边数  */
}MGraph;

//邻接表（适用于稀疏图）
//N个顶点，g[N]数组中每个 g[i]表示与第i个顶点相邻的点串起来形成的链表
//方便找任一顶点的所有邻接点
//节约空间
typedef struct EdgeNode /* 边表结点  */
{
    int adjvex;    /* 邻接点域,存储该顶点对应的下标 */
    EdgeType info;      /* 用于存储权值,对于非网图可以不需要 */
    struct EdgeNode *next; /* 链域,指向下一个邻接点 */
}EdgeNode;

typedef struct VertexNode /* 顶点表结点 */
{
    VertexType data; /* 顶点域,存储顶点信息 */
    EdgeNode *firstedge;/* 边表头指针 */
}VertexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes,numEdges; /* 图中当前顶点数和边数 */
}GraphAdjList;
