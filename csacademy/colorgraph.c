/*
Лора играе логическа игра в интернет. 
Тя получава неориентиран граф с N върха, номерирани от 1 до N. 
Графът е такъв, че между всеки два различни върха има ребро, оцветено или в синьо, или в червено. 
Ще казваме, че графът е червено-свързан, ако можем от всеки връх да достигнем до всеки друг, различен от него, движейки се само по червени ребра. 
Аналогично, графът е синьо-свързан, ако можем от всеки връх да достигнем всеки друг, различен от него, движейки се само по сини ребра. 
Дефинираме състояние на графа като двойка числа (A, B), като:
-	A=1 ако графът е червено-свързан и A=0 ако не е;
-	B=1 ако графът е синьо-свързан и B=0 ако не е
Така например, състояние (1, 0) описва граф, който е червено-свързан, но не е синьо-свързан. 
С едно кликване върху дадено ребро Лора може да промени цвета му (от син в червен или от червен в син). 
Целта на играта е по зададен начален граф и желано състояние, с минимален брой кликвания, началният граф да се промени до такъв, който е в желаното състояние (вижте примера за повече информация). 
Помогнете на Лора, като напишете програма colorgraph, която намира минималния брой необходими кликвания. 
*/
#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

////////////////////////

enum{ MAXN=250};
int n;
int graph[MAXN+10][MAXN+10];
int A,B;
int sA,sB;
bool TFO[MAXN+10];
int L=0;
vec components[MAXN+10];
int flow[MAXN+10][MAXN+10];
int cap[MAXN+10][MAXN+10];
int SOURCE,TARGET;
vec Path;
vec Graph[MAXN+10];
vecp Ans;
bool hasans=false;
vecp Changes;
int q[MAXN+10];
int qL;
int dst[MAXN+10];
int mydegree[MAXN+10];
vec mixed;




void GetAll(int ver,int color)
{
    int i;
    if (TFO[ver])
      return;
    TFO[ver]=true;
    for (i=1;i<=n;i++)
    {
        if (graph[ver][i]==color)
          GetAll(i,color);
    }
    return;
}
void GetState()
{
    int i,j;
    sA=1;
    sB=1;
    memset(TFO,false,sizeof(TFO));
    GetAll(1,0);
    for (i=1;i<=n;i++){
        if (!TFO[i]){
            sA=0;
            break;
        }
    }
    memset(TFO,false,sizeof(TFO));
    GetAll(1,1);
    for (i=1;i<=n;i++){
        if (!TFO[i]){
            sB=0;
            break;
        }
    }
    return;
}
void DFS(int ver,int c)
{
    if (TFO[ver])
      return;
    TFO[ver]=true;
    components[c].ptr = pushback(components[c].ptr, &components[c].sz, ver);
    int i;
    for (i=1;i<=n;i++){
        if (graph[ver][i]==0)
          DFS(i,c);
    }
    return;
}
void GetComponents()
{
    int i;
    memset(TFO,false,sizeof(TFO));
    for (i=1;i<=n;i++){
        if (!TFO[i]){
            L++;
            DFS(i,L);
        }
    }
    return;
}
bool GetPath(int ver)
{
    if (TFO[ver])
      return false;
    TFO[ver]=true;
    Path.ptr = pushback(Path.ptr, &Path.sz, ver);
    if (ver==TARGET)
      return true;
    int i;
    for (i=0; i<Graph[ver].sz; i++){
        if ( flow[ver][ Graph[ver].ptr[i] ] < cap[ver][ Graph[ver].ptr[i] ] ){
            if (GetPath(Graph[ver].ptr[i]))
              return true;
        }
    }
    Path.sz--;
    return false;
}
void Reachables(int ver)
{
    if (TFO[ver])
      return;
    TFO[ver]=true;
    int i;
    for (i=1;i<=n;i++){
        if (flow[ver][i]<cap[ver][i])
          Reachables(i);
    }
    return;
}
void GetCut()
{
    int i,j;
    memset(TFO,false,sizeof(TFO));
    Reachables(SOURCE);
    Changes.sz=0;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if (TFO[i] && !TFO[j]  && cap[i][j]>0)
                Changes.ptr = pushbackP(Changes.ptr, &Changes.sz, newPair(i,j));
        }
    }
    if(!hasans || Ans.sz > Changes.sz){
        Ans.sz=0;
        for(i=0; i<Changes.sz; i++)
            Ans.ptr = pushbackP(Ans.ptr, &Ans.sz, Changes.ptr[i]);
        hasans=true;
    }
    return;
}
void SendFlow()
{
    int i;
    for (i=1; i<Path.sz; i++){
        flow[ Path.ptr[i-1] ][ Path.ptr[i  ] ]++;
        flow[ Path.ptr[i  ] ][ Path.ptr[i-1] ]--;
    }
    return;
}
bool BFSLevel()
{
    int i,j;
    int uk=1;
    bool goodret=false;
    for (i=1;i<=n;i++)
        Graph[i].sz=0;
    qL=1;
    q[1]=SOURCE;
    dst[SOURCE]=0;
    TFO[SOURCE]=true;
    while(uk<=qL){
        if (q[uk]==TARGET){
            goodret=true;
            break;
        }
        for (i=1;i<=n;i++){
            if (!TFO[i] && flow[ q[uk] ][i]<cap[ q[uk] ][i]){
                qL++;
                q[qL]=i;
                dst[i]=dst[ q[uk] ]+1;
                TFO[i]=true;
            }
        }
        uk++;
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            if (flow[i][j]<cap[i][j] && dst[i]==dst[j]-1)
                Graph[i].ptr = pushback(Graph[i].ptr, &Graph[i].sz, j);
    return goodret;
}
void GetMinCut()
{
    int flowctr=0;
    memset(TFO,false,sizeof(TFO));
    while(BFSLevel()){
        memset(TFO,false,sizeof(TFO));
        Path.sz=0;
        while(GetPath(SOURCE)){
            SendFlow();
            flowctr++;
            if(hasans && flowctr >= Ans.sz)
              return;
            Path.sz=0;
            memset(TFO,false,sizeof(TFO));
        }
        memset(TFO,false,sizeof(TFO));
    }
    GetCut();
    return;
}
void DisconnectGraph()
{
    int i,j;
    for (i=1;i<=n;i++){
        cap[i][i]=0;
        for (j=i+1;j<=n;j++){
            if (graph[i][j]==0){
                cap[i][j]=1;
                cap[j][i]=1;
            }
            else{
                cap[i][j]=0;
                cap[j][i]=0;
            }
        }
    }
    SOURCE=1;
    for (i=2;i<=n;i++){
        memset(flow,0,sizeof(flow));
        TARGET=i;
        GetMinCut();
    }
    return;
}
void FlipInput()
{
    int i,j;
    int swp;
    swp=A;
    A=B;
    B=swp;
    swp=sA;
    sA=sB;
    sB=swp;
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++)
            graph[i][j]^=1;
    return;
}
int main()
{
    int i,j;
    int isolated,spec;
    int edges=0;
    int sum=0;
    int uk=0;
    scanf("%d",&n);
    for (i=1;i<=n;i++){
        sum=0;
        for (j=1;j<=n;j++){
            scanf("%d",&graph[i][j]);
            sum+=graph[i][j];
        }
    }
    scanf("%d %d",&A,&B);
    GetState();
    if (A==sA && B==sB){
        printf("0\n");
        return 0;
    }
    if (A==0 && B==0){
        printf("-1\n");
        return 0;
    }
    if (A==1 && B==1){
        if (sA==1 && sB==0)
            FlipInput();
        if (n==3){
            printf("-1\n");
            return 0;
        }
        GetComponents();
        for (i=1;i<=n;i++){
            for (j=i+1;j<=n;j++){
                if (graph[i][j]==0){
                    edges++;
                    mydegree[i]++;
                    mydegree[j]++;
                }
            }
        }
        if( L==2 && (components[1].sz==1 || components[2].sz==1) && edges==( (n-1)*(n-2)/2 ) ){
            if (components[1].sz==1)
              isolated=components[1].ptr[0];
            else
              isolated=components[2].ptr[0];
            printf("2\n");
            if (isolated==1)
              spec=2;
            else
              spec=1;
            printf("%d %d\n",isolated,spec);
            if (isolated==2 || spec==2)
              printf("%d 3\n",spec);
            else
              printf("%d 2\n",spec);
            return 0;
        }
        mixed.sz=0;
        for (i=0;i<components[1].sz;i++)
            mixed.ptr = pushback(mixed.ptr, &mixed.sz, components[1].ptr[i]);
        uk=0;
        printf("%d\n",L-1);
        for (i=2;i<=L;i++){
            while(mydegree[ mixed.ptr[uk] ]>=n-2)
              uk++;
            printf("%d %d\n", mixed.ptr[uk], components[i].ptr[0]);
            mydegree[ mixed.ptr[uk] ]++;
            mydegree[ components[i].ptr[0] ]++;
            for(j=0;j<components[i].sz;j++)
                mixed.ptr = pushback(mixed.ptr, &mixed.sz, components[i].ptr[j]);
        }
    }
    else{
        if (A==1 && B==0)
            FlipInput();
        DisconnectGraph();
        printf("%d\n", Ans.sz);
        for (i=0; i<Ans.sz; i++)
            printf("%d %d\n", Ans.ptr[i].first, Ans.ptr[i].second);
    }
    return 0;
}

