#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
enum{ MAXPLACES = 1000};
const double INF = 848238233.;

typedef struct{
    int x, y, f;
}trip;
trip newtrip(int x, int y, int f){
    return(trip){x,y,f};
}
trip places[MAXPLACES];
double dist  [MAXPLACES][MAXPLACES];
int    parent[MAXPLACES][MAXPLACES];

double euc(trip*a, trip*b){
    int difx = a->x - b->x;
    int dify = a->y - b->y;
    int diff = 5*(a->f - b->f);
    return sqrt(difx*difx + dify*dify + diff*diff);
}
int main(){
    dfill(dist  , MAXPLACES, MAXPLACES, INF);
    dfill(parent, MAXPLACES, MAXPLACES, -1 );
    int N, M, a, b;
    char*name;
    char*type;
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; ++i){
        scanf("%d%d%d", &places[i].f, &places[i].x, &places[i].y);
        dist[i][i] = 0;
    }
    for(int i = 0; i < M; ++i){
        scanf("%d %d", &a, &b);
        type=getstr();
        double d = euc(&places[a], &places[b]);
        if (type[1] == 's'){
            dist[a][b] = fmin(dist[a][b], 1.);
            dist[b][a] = fmin(dist[b][a], d*3);
        }
        else if (type[0] == 'l') {
            dist[a][b] = fmin(dist[a][b], 1.);
            dist[b][a] = fmin(dist[b][a], 1.);
        }
        else {
            dist[a][b] = fmin(dist[a][b], d);
            dist[b][a] = fmin(dist[b][a], d);
        }
    }
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i == j || dist[i][j] == INF)
                parent[i][j] = -1;
            else
                parent[i][j] = i;
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                double newD = dist[i][k] + dist[k][j];
                if (newD < dist[i][j]) {
                    dist[i][j] = newD;
                    parent[i][j] = parent[k][j];
                }
            }
    int result[MAXPLACES];
    int Q;
    scanf("%d", &Q);
    for(int q = 0; q < Q; ++q){
        scanf("%d%d", &a, &b);
        int i = 0;
        result[i++] = b;
        while((b = parent[a][b]) != -1)
            result[i++] = b;
        for(int j = i-1; j >= 0; --j){
            if (j < i-1)
                printf(" ");
            printf("%d", result[j]);
        }
        puts("");
    }
    return 0;
}
