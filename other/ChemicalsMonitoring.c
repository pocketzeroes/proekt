#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)

int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

enum{ max_start    = 1000000000};
enum{ max_duration = 1000000000};

typedef struct{
    int s, d, p, next;
}Stream;

Stream newStream(int s, int d, int p, int next){
    return(Stream){s,d,p,next};
}
int cmpS(const void*pa, const void*pb){
    Stream*lhs=(Stream*)pa;
    Stream*rhs=(Stream*)pb;
    return(lhs->s < rhs->s || (lhs->s == rhs->s && lhs->d > rhs->d))?-1:1;
}
Stream*streams; 
int    streams_sz;
int**profit;

int solve(int i, int j){
    if(j < i || j >= streams_sz || streams[i].s + streams[i].d < streams[j].s)
        return 0;
    if(profit[i][j] != -1)
        return profit[i][j];
    if(i == j)
        return (profit[i][i] = streams[i].p + solve(i, i + 1));
    if(streams[i].s + streams[i].d < streams[j].s + streams[j].d)
        return (profit[i][j] = solve(i, j + 1));
    return(profit[i][j] = max(solve(i, j + 1), solve(j, j) + solve(i, streams[j].next)));
}
int main(){
    int n;
    while(scanf("%d", &n)==1){
        streams_sz=n+1;
        streams = calloc(streams_sz, sizeof(Stream));
        streams[0] = newStream(-1, max_start+max_duration+2, 0, -1);
        for(int i = 1; i <= n; i++){
            scanf("%d %d %d", &streams[i].s, &streams[i].d, &streams[i].p);
            streams[i].next = -1;
        }
        qsort(streams, streams_sz, sizeof(Stream), cmpS);
        for (int i = 0; i < streams_sz; i++){
            for (int j = i + 1; j < streams_sz; j++){
                if (streams[j].s >= streams[i].s + streams[i].d){
                    streams[i].next = j;
                    break;
                }
            }
        }
        profit = newmat(n+1, n+1); dfill(profit, n+1, n+1, -1);
        printf("%d\n", solve(0, 0));
    }
    return 0;
}
