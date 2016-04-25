//无向图有重边强连通分量hdu4612
// @author czw

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

const int MAXN = 200010;//点数
const int MAXM = 2000010;//边数，因为是无向图，所以这个值要*2

struct Edge
{
    int to,next;
    bool cut;//是否是桥标记
} edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1~block
int Index,top;
int vis[MAXM];
int block;//边双连通块数
bool Instack[MAXN];
int bridge;//桥的数目
int N, M;

void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];edge[tot].cut=false;
    head[u] = tot++;
}

void Tarjan(int u,int pre)
{
    //printf("u=%d\n",u);
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        //printf("i=%d\n",i);
        if(vis[i]) continue;
        vis[i] = 1;
        vis[i^1] = 1;
        v = edge[i].to;
        //if(v == pre)continue;
        if( !DFN[v] )
        {
            Tarjan(v,u);
            if( Low[u] > Low[v] )Low[u] = Low[v];
            if(Low[v] > DFN[u])
            {
                bridge++;
                edge[i].cut = true;
                edge[i^1].cut = true;
            }
        }
        else if( Instack[v] && Low[u] > DFN[v] )
            Low[u] = DFN[v];
    }
    if(Low[u] == DFN[u])
    {
        block++;
        do
        {
            v = Stack[--top];
            Instack[v] = false;
            Belong[v] = block;
        }
        while( v!=u );
    }
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(DFN,0,sizeof(DFN));
    memset(vis,0,sizeof(vis));
    memset(Instack,false,sizeof(Instack));
    Index = top = block = 0;
}

int maxDep = 0;
int maxDepV = 0;
void dfs(int u, int d) {
    int v;
    DFN[u] = 1;
    if(d > maxDep) {
        maxDep = d;
        maxDepV = u;
    }
    for(int i = head[u]; i != -1; i = edge[i].next) {
        v = edge[i].to;
        if(DFN[v]) continue;
        dfs(v, d+(Belong[u]==Belong[v]?0:1));
        //在同组里深度不变化 不在同一分量里深度+1
    }
}

int main() {
    while(~scanf("%d %d", &N, &M) && N) {
        init();
        while(M--) {
            int fr, to;
            scanf("%d %d", &fr, &to);
            addedge(fr, to);
            addedge(to, fr);
        }
        int cnt = 0;
        for(int i = 1; i <= N; i++) 
            if(!DFN[i]) {
                Tarjan(i, 0);
                cnt++;
            }
        maxDep = -1;
        memset(DFN, 0, sizeof(DFN)); // temply used as used[SIZE]
        for(int i = 1; i <= N; i++)
            if(!DFN[Belong[i]]) dfs(i, 0);
        //printf("%d\n%d\n-----\n",maxDepV,maxDep);
        
        memset(DFN, 0, sizeof(DFN)); 
        dfs(maxDepV, 0);
        //printf("%d\n%d\n%d\n",block,maxDep,cnt);
        printf("%d\n",block - maxDep - cnt);
    }
    
    return 0;
}