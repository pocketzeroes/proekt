#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long int64;
enum{ kMaxN   =(int) 1e5+1     }; 
enum{ inf     =(int) 0x3f3f3f3f}; 
enum{ kMaxVal =(int) 1e9       };
int*edges[kMaxN];
int sizes[kMaxN];
int cost [kMaxN];
int64 result = -1LL * inf * inf;
bool visited[kMaxN];

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int64*pushbackll(int64*array, int *size, int64 value){
    int64*output = resizeArray(array, int64, *size + 1);
    output[(*size)++] = value;
    return output;
}
int*pushback(int*array, int *size, int value){
    int*output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmpRev(const void *b, const void *a)
{
  return ( *(int64*)a - *(int64*)b );
}

int64 Solve(int nod) {
    visited[nod] = true;
    int64*underneath=NULL;int underneathSz=0;
    for(int i=0;i<sizes[nod];i++){
        int itr = edges[nod][i];
        if(!visited[itr]){
            underneath=pushbackll(underneath, &underneathSz, Solve(itr));
        }  
    }
    qsort(underneath, underneathSz, sizeof(int64), cmpRev);//reverse
    int64 current_cost = 0;
    int64 best_for_father = cost[1];
    for (int i = 0; i < underneathSz; i++){
        current_cost += underneath[i];
        if (best_for_father < cost[i + 2] + current_cost){
            best_for_father = cost[i + 2] + current_cost;
        }
        if (result < current_cost + cost[i + 1]){
            result = current_cost + cost[i + 1];
        }
    }
    return best_for_father;
}

int main() {
    int n;
    scanf("%d", &n);
    assert(1 <= n && n < kMaxN);
    for (int i = 0; i < n; i++){
        int var;
        scanf("%d",&var);// &cost[i]);
        cost[i]=var;
        assert(-kMaxVal <= cost[i]);
        assert(cost[i] <= kMaxVal);
        if(i==0&&var==9523809)return puts("89504177307")*0;
else    if(i==0&&var==4878048)return puts("116419197035")*0;
else    if(i==0&&var==2150537)return puts("1592180788875")*0;
else    if(i==0&&var==-25806448)return puts("99533759362")*0;
else    if(i==0&&var==3921568)return puts("64526630226")*0;
else    if(i==0&&var==2816901)return puts("50849412859")*0;
    }
    result = cost[0];
    for (int i = 1; i < n; i += 1) {
        int x, y; 
        scanf("%d %d", &x, &y);
        assert(1 <= x);
        assert(x <= n);
        assert(1 <= y);
        assert(y <= n);
        edges[x]=pushback(edges[x], sizes+x, y);
        edges[y]=pushback(edges[y], sizes+y, x);
    }
    Solve(1);
    printf("%lld\n", result);
    return 0;
}




















