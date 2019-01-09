#include<iostream>
#include<queue>

using namespace std;

#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define INFINITY 65535

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef char VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef enum {
    ORIENTED,    //有向图
    UNDIRECTED,  //无向图
} GraphType;

//邻接矩阵的好处： 直观简单好理解；方便检查任意一对顶点间是否存在边
//  方便找任一顶点的所有邻接点；方便计算任一顶点的度
//坏处： 对于稀疏图来说浪费空间和浪费时间

typedef struct
{
    VertexType vexs[MAXVEX]; /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int numNodes, numEdges; /* 图中当前的顶点数和边数  */
    GraphType type;
}MGraph;

//邻接表（适用于稀疏图）
//N个顶点，g[N]数组中每个 g[i]表示与第i个顶点相邻的点串起来形成的链表
//方便找任一顶点的所有邻接点
//节约空间
typedef struct EdgeNode /* 边表结点  */
{
    int adjvex;    /* 邻接点域,存储该顶点对应的下标（在AdjList[]数组中的下标） */
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
    GraphType type;
}GraphAdjList;



//DFS, depth first search, 深度优先搜索
//类似于树的先序遍历
//若有N个顶点，E条边，时间复杂度：
//邻接表： O(N+E) 其扫描邻接点更为方便
//邻接矩阵： O(N^2)，扫描N遍以得到邻接点

void DFS_inner(int idx, int visited[], MGraph& graph) {
    visited[idx] = 1;
    for(int j = 0; j< graph.numNodes; j++){
        if(j != idx && (
          (graph.type == UNDIRECTED && graph.arc[idx][j] != 0) /*无向图相邻点*/ ||
          (graph.type == ORIENTED && (graph.arc[idx][j] != INFINITY || graph.arc[j][idx] != INFINITY))
          /*有向图邻接点*/ ))
        {
            if(visited[j] == 0) {
                DFS_inner(j, visited, graph);
            }
        }
    }//for
}

void DFS(int idx, MGraph& graph){
    int visited[MAXVEX] = {0};
    DFS_inner(idx, visited, graph);
}

void DFS_inner_adj_list(int idx, int visited[], GraphAdjList& graph) {
    visited[idx] = 1;
    EdgeNode * ep = graph.adjList[idx].firstedge;//取得头指针
    while(ep->next != NULL){
        ep = ep->next;//当下一个不为空时处理下一个
        if(visited[ep->adjvex] == 0){
            DFS_inner_adj_list(ep->adjvex, visited, graph);
        }
    }
}

void DFS_adj_list(int idx, GraphAdjList& graph){
    int visited[MAXVEX] = {0};
    DFS_inner_adj_list(idx, visited, graph);
}

//BFS, breadth first search,广度优先搜索
//类似于树的层序遍历
//若有N个顶点，E条边，时间复杂度与DFS一样

void BFS_inner(int idx, int visited[], MGraph& graph, queue<int>& q){
    visited[idx] = 1;
    q.push(idx);
    while(!q.empty()){
        int i = q.front();
        q.pop();
        for(int j = 0; j< graph.numNodes; j++){
            if(j != i && (
              (graph.type == UNDIRECTED && graph.arc[i][j] != 0) /*无向图相邻点*/ ||
              (graph.type == ORIENTED && (graph.arc[i][j] != INFINITY || graph.arc[j][i] != INFINITY))
              /*有向图邻接点*/ ))
            {
                if(visited[j] == 0) {
                    visited[j] = 1;
                    q.push(i);
                }
            }
        }//for
    }
}

void BFS(int idx, MGraph& graph){
    int visited[MAXVEX] = {0};
    queue<int> q;
    BFS_inner(idx, visited, graph, q);
}

void BFS_inner_adj_list(int idx, int visited[], GraphAdjList& graph, queue<int>& q){
    visited[idx] = 1;
    q.push(idx);
    while(!q.empty()){
        int i = q.front();
        q.pop();
        EdgeNode * ep = graph.adjList[i].firstedge;//取得头指针
        while(ep->next != NULL){
            ep = ep->next;//当下一个不为空时处理下一个
            if(visited[ep->adjvex] == 0){
                visited[ep->adjvex] = 1;
                q.push(ep->adjvex);
            }
        }
    }
}

void BFS_adj_list(int idx, GraphAdjList& graph){
    int visited[MAXVEX] = {0};
    queue<int> q;
    BFS_inner_adj_list(idx, visited, graph, q);
}
