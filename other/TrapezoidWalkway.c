#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

////////////////////////
typedef struct trap{
    int bases[2];
    int h;
    int dArea;
}trap;
trap newtrap(int mya, int myb, int myh){
    trap rez;
    rez.bases[0] = mya;
    rez.bases[1] = myb;
    rez.h = myh;
    rez.dArea = (rez.bases[0]+rez.bases[1])*myh;
    return rez;
}
int n;
trap*list;
int**adj;

int main(){
    n = in_nextInt();
    while(n != 0){
        list = calloc(n, sizeof(trap));
        for(int i=0; i<n; i++){
            int a = in_nextInt();
            int b = in_nextInt();
            int h = in_nextInt();
            list[i] = newtrap(a, b, h);
        }
        int start = in_nextInt();
        int end   = in_nextInt();
        adj = newmat(2*n+1, 2*n+1);
        fill(adj[2*n], 2*n+1, -1);
        adj[2*n][2*n] = 0;
        for(int i=0; i<2*n; i++){
            for(int j=0; j<2*n; j++){
                if(i/2 == j/2)
                    continue;
                if(list[i/2].bases[i%2] == list[j/2].bases[j%2])
                    adj[i][j] = list[j/2].dArea;
                else
                    adj[i][j] = -1;
            }
            if(list[i/2].bases[i%2] == start)
                adj[2*n][i] = list[i/2].dArea;
        }
        int*d = calloc(2*n+1, sizeof(int)); fill(d, 2*n+1, 2000000001);
        d[2*n] = 0;
        bool*used = calloc(2*n+1, sizeof(bool));
        for(int i=0; i<2*n; i++){
            int index = -1;
            for(int j=0; j<=2*n; j++){
                if(used[j])
                    continue;
                if(index == -1 || d[j] < d[index])
                    index = j;
            }
            used[index] = true;
            for(int j=0; j<=2*n; j++)
                if(adj[index][j] != -1)
                    d[j] = fmin(d[j], d[index]+adj[index][j]);
        }
        int res = -1;
        if(start == end)
            res = 0;
        else{
            for(int i=0; i<2*n; i++)
                if(list[i/2].bases[0] == end || list[i/2].bases[1] == end)
                    if(res == -1 || d[i] < res)
                        res = d[i];
        }
        printf("%.2f\n", res/100.0);
        freemat(adj, 2*n+1);
        free(list);
        free(d);
        free(used);
        n = in_nextInt();
    }
    return 0;
}
