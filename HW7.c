// ---
// title: 最小生成树Kruskal算法
// date: 2022-12-03 21:26:45
// excerpt:
// tags: Data_Structure MST Kruskal
// rating: ⭐⭐
// status: Complete
// share: false
// ---

// 假定每对顶点表示图的一条边，每条边对应一个权值
// 1. 实现从文本文件读入每条边的顶点和权值
// 2. 根据读入的数据，构造图的数据结构
// 3. 采用Kruskal算法求出最小生成树
// 4. 打印输出最小生成树边的顶点及权值
// 5. 独立完成实验报告

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

typedef struct
{
    int vex;
    int gno;
} TVex;

typedef struct
{
    int vh, vt;
    int cost;
    int flag;
} TEdge;

typedef struct
{
    TVex *pv;
    TEdge *pe;
    int nv, ne;
} TGraph, *PGraph;

//读取文件，size需要预先给定，文本数据里使用空格间隔，
//g为储存的邻接矩阵，flag判断是否为有向图，传出int为边的数量
int read_file(int g[SIZE][SIZE], char *filename, int flag)
{
    FILE *fp = NULL;
    int i, j;
    int edgelen = 0;
    // 打开文件
    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("read_file(): 打开文件%s失败!\n", filename);
        exit(0);
    }
    else
    {
        printf("read_file(): 成功打开文件%s!\n", filename);
    }
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            fscanf(fp, "%d", &g[i][j]);
            if (g[i][j] != 0)
            {
                edgelen++;
            }
        }
        fscanf(fp, "\n");
    }
    fclose(fp);
    printf("read_file(): 成功读入文件%s!\n", filename);
    fclose(fp);
    if (flag == 1)
    {
        return edgelen;
    }
    else
    {
        return edgelen / 2;
    }
}

//把邻接矩阵g的数据储存到顶点节点和边节点
void init_graph(TVex *pv, TEdge *pe, int g[SIZE][SIZE], int edgelen, int flag)
{
    int l = 0;
    for (int i = 0; i < SIZE; i++)
    {
        pv[i].vex = i + 1;
        pv[i].gno = i + 1;
    }
    for (int j = 0; j < SIZE; j++)
    {
        for (int k = j; k < SIZE; k++)
        {
            if (*(*(g + j) + k) != 0)
            {
                pe[l].cost = *(*(g + j) + k);
                pe[l].vh = j + 1;
                pe[l].vt = k + 1;
                pe[l].flag = 0;
                l++;
                if ((flag == 0) && (l == edgelen))
                {
                    break;
                }
            }
            if ((flag == 0) && (l == edgelen))
            {
                break;
            }
        }
        if ((flag == 0) && (l == edgelen))
        {
            break;
        }
    }
}

//kruskal算法，传入树的地址
void kruskal_mst(TGraph *G)
{
    int i, min, idx, m, n, g, count = 1;
    while (count < G->nv)
    { // 逐一加入 n-1 条边
        min = INT_MAX;
        for (i = 0; i < G->ne; ++i)
        { // 选取未访问过的最小权边
            if (G->pe[i].cost < min && G->pe[i].flag == 0)
            {
                min = G->pe[i].cost;
                idx = i;
            }
        }
        m = G->pe[idx].vh;
        n = G->pe[idx].vt;
        if (G->pv[m].gno != G->pv[n].gno)
        {
            G->pe[idx].flag = 1;
            count++;
            g = G->pv[n].gno;
            for (i = 1; i <= G->nv; ++i)
            {
                if (G->pv[i].gno == g)
                    G->pv[i].gno = G->pv[m].gno;
            }
        }
        else
            G->pe[idx].flag = -1;
    }
}

//输出打印MST
void print_mst(TGraph G)
{
    for (int t = 0; t < G.ne; t++)
    {
        if (G.pe[t].flag == 1)
        {
            printf("%d - %d || cost: %d \n", G.pe[t].vh, G.pe[t].vt, G.pe[t].cost);
        }
    }
}

int main()
{
    int graph[SIZE][SIZE];
    int flag = 0; // 0表示无向图，1表示有向图；
    int edgelen = 0;
    edgelen = read_file(graph, "MST.txt", flag);
    TGraph G;
    TVex pv[SIZE];
    TEdge pe[edgelen];
    G.ne = edgelen;
    G.nv = SIZE;
    G.pv = &pv;
    G.pe = &pe;
    init_graph(pv, pe, graph, edgelen, flag);
    kruskal_mst(&G);
    print_mst(G);
    return 0;
}