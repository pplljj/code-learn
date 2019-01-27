#include<iostream>
#include<queue>
#include<stdio.h>

using namespace std;

#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
#define INFINITY 65535

typedef int Status; /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int VertexType; /* 顶点类型应由用户定义  */
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
                    q.push(j);
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



//连通分量： 无向图的极大连通子图

//强连通： 有向图中两顶点存在双向路径
//强连通图： 有向图中任意两顶点均强连通
//强连通分量： 有向图的极大强连通子图


//无权图的单源最短路径算法
//按照递增（非递减）的顺序找出各个顶点的最短路
//如果使用邻接表实现，T=O(|V|+|E|)
//使用邻接矩阵实现，T=O(|V|^2)

void UnweightedShortestPath(int idx, MGraph& graph,
                         int dist[],   /*数组大小:MAXVEX，元素初始化为-1*/
                         int path[]) /*数组大小:MAXVEX，path[i]表示到达i点前经过的点的索引*/
{
    queue<int> q;
    q.push(idx);
    dist[idx] = 0;
    path[idx] = idx;
    while(!q.empty()){
        int i = q.front();
        q.pop();
        for(int j = 0; j< graph.numNodes; j++){
            if(j != i && (
              (graph.type == UNDIRECTED && graph.arc[i][j] != 0) /*无向图相邻点*/ ||
              (graph.type == ORIENTED && (graph.arc[i][j] != INFINITY || graph.arc[j][i] != INFINITY))
              /*有向图邻接点*/ ))
            {
                if(dist[j] == -1) {
                    dist[j] =dist[i] + 1;
                    //当前j点的上一个经过的点是i，j是i的邻接点
                    //这样求到的path[]数组可以逆向还原出最短路径
                    //设终点为d,起点为s，则终点前一点为path[d],path[d]前一点为path[path[d]]
                    //不断迭代，直到path[x] = x = s时，即逆序求出最短路径
                    path[j] = i;
                    q.push(j);
                }
            }
        }//for
    }
}

//Dijkstra
//.............|
//集合S       w |
//       s*    |   v
//.............|
//如上图，s*和w均已被收集进S集合中，v还在外面, v与w邻接
//加入v前，源点到w只经过S中的点
//加入v之后，可能的情况是 dist[w] > dist[v] + |v,w|
//这时需要更新dist[w]

typedef int Patharc[MAXVEX];    /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX];/* 用于存储到各点最短路径的权值和 */

void Dijkstra_ShortestPath(MGraph& G, int v0, Patharc *P, ShortPathTable *D) {
    int v,w,k,min;
    int final[MAXVEX];/* final[w]=1表示求得顶点v0至vw的最短路径 */

    for(v=0; v<G.numNodes; v++)    /* 初始化数据 */
    {
        final[v] = 0;           /* 全部顶点初始化为未知最短路径状态 */
        //arc中无穷大表示无邻接, arc[i][i]=0
        (*D)[v] = G.arc[v0][v];/* 将与v0点有连线的顶点加上权值 */
        (*P)[v] = 0;                /* 初始化路径数组P为0  */
    }

    (*D)[v0] = 0;  /* v0至v0路径为0 */
    final[v0] = 1;    /* v0至v0不需要求路径 */

    /* 开始主循环，每次求得v0到某个v顶点的最短路径 */
    for(v=1; v<G.numNodes; v++)  //v在for循环中并没有用到，因为我们只需循环 |V|-1 次
    {
        min=INFINITY;    /* 当前所知离v0顶点的最近距离 */
        for(w=0; w<G.numNodes; w++) /* 寻找离v0最近的顶点 */
        {
            if(!final[w] && (*D)[w]<min)
            {
                k=w;
                min = (*D)[w];    /* w顶点离v0顶点更近 */
            }
        }
        final[k] = 1;    /* 将目前找到的最近的顶点置为1 */
        for(w=0; w<G.numNodes; w++) /* 修正当前最短路径及距离 */
        {
            /* 如果经过v顶点的路径比现在这条路径的长度短的话 */
            if(!final[w] && (min+G.arc[k][w]<(*D)[w]))
            { /*  说明找到了更短的路径，修改D[w]和P[w] */
                (*D)[w] = min + G.arc[k][w];  /* 修改当前路径长度 */
                (*P)[w]=k;
            }
        }
    }
    return;
}

void Print_Dijkstra_Res(MGraph& G, Patharc P, ShortPathTable D, int v0) {
    int i,j;
    printf("Shortest path in reverse order:\n");
    for(i=1;i<G.numNodes;++i)
    {
        printf("v%d - v%d : ",v0,i);
        j=i;
        while(P[j]!=0)
        {
            printf("%d ",P[j]);
            j=P[j];
        }
        printf("\n");
    }
    printf("\nshortest distance from source to node:\n");
    for(i=1;i<G.numNodes;++i)
        printf("v%d - v%d : %d \n",G.vexs[0],G.vexs[i],D[i]);
}

//时间复杂度分析：
//找最小的dist： 1.直接扫描所有的未收录顶点-O(|V|)
//               T = O(|V|^2 + |E|)   内外循环|V|^2   访问边 |E|
//               对于稠密图效果好

//             2.将dist存在最小堆中 - O(log|V|)
//               更新dist值 - O(log|V|)
//               T = O(|V|log|V| + |E|log|V|) = O(|E|log|V|)
//               对于稀疏图效果好


//Floyd
//T=O(|V|^3)

typedef int Patharc2D[MAXVEX][MAXVEX];
typedef int ShortPathTable2D[MAXVEX][MAXVEX];

/* Floyd算法，求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w]。 */
void ShortestPath_Floyd(MGraph& G, Patharc2D *P, ShortPathTable2D *D)
{
    int v,w,k;
    for(v=0; v<G.numNodes; ++v) /* 初始化D与P */
    {
        for(w=0; w<G.numNodes; ++w)
        {
            (*D)[v][w]=G.arc[v][w]; /* D[v][w]值即为对应点间的权值 */
            (*P)[v][w]=w;               /* 初始化P */
        }
    }
    for(k=0; k<G.numNodes; ++k)
    {
        for(v=0; v<G.numNodes; ++v)
        {
            for(w=0; w<G.numNodes; ++w)
            {
                if ((*D)[v][w]>(*D)[v][k]+(*D)[k][w])
                {/* 如果经过下标为k顶点路径比原两点间路径更短 */
                    (*D)[v][w]=(*D)[v][k]+(*D)[k][w];/* 将当前两点间权值设为更小的一个 */
                    (*P)[v][w]=(*P)[v][k];/* 路径设置为经过下标为k的顶点 */
                }
            }
        }
    }
}

void Print_Floyd_Res(MGraph& G, Patharc2D P, ShortPathTable2D D) {
    int v,w,k;
    printf("shortest path:\n");
    for(v=0; v<G.numNodes; ++v)
    {
        for(w=v+1; w<G.numNodes; w++)
        {
            printf("v%d-v%d weight: %d ",v,w,D[v][w]);
            k=P[v][w];              /* 获得第一个路径顶点下标 */
            printf(" path: %d",v);  /* 打印源点 */
            while(k!=w)             /* 如果路径顶点下标不是终点 */
            {
                printf(" -> %d",k); /* 打印路径顶点 */
                k=P[k][w];          /* 获得下一个路径顶点下标 */
            }
            printf(" -> %d\n",w);   /* 打印终点 */
        }
        printf("\n");
    }

    printf("shortest distance D\n");
    for(v=0; v<G.numNodes; ++v)
    {
        for(w=0; w<G.numNodes; ++w)
        {
            printf("%d\t",D[v][w]);
        }
        printf("\n");
    }
    printf("shortest distance P\n");
    for(v=0; v<G.numNodes; ++v)
    {
        for(w=0; w<G.numNodes; ++w)
        {
            printf("%d ",P[v][w]);
        }
        printf("\n");
    }
}
