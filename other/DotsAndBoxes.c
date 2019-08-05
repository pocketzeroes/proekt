#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ inf=0x3f3f3f3f};
enum{ N=200         };
int L[]={0,1,0,-1};
int R[]={1,0,-1,0};
char Graph[N<<1][N<<1];

typedef struct edge_t{
    int v,c,next;
}edge_t;
edge_t edge[N*N*4];
int Ecnt;
int vertex[N*N];
int LL[N*N];

void init_Graph(){
    Ecnt=0;
    memset(vertex,-1,sizeof(vertex));
}
void make_edge(int u,int v,int c){
    edge[Ecnt].v=v;
    edge[Ecnt].c=c;
    edge[Ecnt].next=vertex[u];
    vertex[u]=Ecnt++;
    edge[Ecnt].v=u;
    edge[Ecnt].c=0;
    edge[Ecnt].next=vertex[v];
    vertex[v]=Ecnt++;
}
bool bfs(int s,int t){
    memset(LL,-1,sizeof(LL));
    vec q=newVec();
    q.ptr = pushback(q.ptr, &q.sz, s);
    LL[s]=0;
    while(q.sz>0){
        int u=q.ptr[q.sz-1]; q.sz--;
        for(int i=vertex[u]; i!=-1; i=edge[i].next){
            if(edge[i].c<=0) 
                continue;
            int v=edge[i].v;
            if(-1!=LL[v]) 
                continue;
            q.ptr = pushback(q.ptr, &q.sz, v);
            LL[v]=LL[u]+1;
        }
    }
    return -1!=LL[t];
}
int dfs(int u,int cf,int t){
    if(u==t) 
        return cf;
    int tf=0;
    for(int i=vertex[u]; i!=-1; i=edge[i].next){
        int v=edge[i].v;
        int c=edge[i].c;
        if(LL[u]+1==LL[v]&&c>0&&cf>tf){
            int f=dfs(v,min(c,cf-tf),t);
            if(0==f) 
                continue;
            edge[i].c-=f;
            edge[i^1].c+=f;
            tf+=f;
        }
    }
    if(0==tf) 
        LL[u]=-1;
    return tf;
}
int Dinic(int s,int t){
    int ret=0;
    while(bfs(s,t)){
        int ans;
        while(ans=dfs(s,inf,t))
            ret+=ans;
    }
    return ret;
}
inline int Gethash(int x,int y,int N){
    return x*N+y;
}
int main(){
    int N;
    while(scanf("%d",&N)!=EOF){
        init_Graph();
        int s=(N+1)*(N+1),e=(N+1)*(N+1)+1;
        for(int i=0;i<2*N-1;i++)
            scanf("%s",Graph[i]);
        for(int i=0;i<=N;i++){
            for(int j=0;j<=N;j++){
                int color=(i+j)%2;
                int flow=(i==0||j==0||i==N||j==N)?4:3;
                int x=2*i-1,y=2*j-1;
                for(int k=0;k<4;k++){
                    int m=x+L[k],n=y+R[k];
                    if(m>=0&&m<2*N-1&&n>=0&&n<2*N-1&&Graph[m][n]=='.'){
                        make_edge(Gethash(i,j,N+1),Gethash(i+L[k],j+R[k],N+1),1);
                    }
                    else 
                        flow--;
                }
                if(color==0)
                    make_edge(s,Gethash(i,j,N+1),flow);
                else
                    make_edge(Gethash(i,j,N+1),e,flow);
            }
        }
        printf("%d\n",Dinic(s,e)+1);
    }
    return 0;
}
