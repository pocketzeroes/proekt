#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{MAXN = 105};
int N;
char*S;
char*T = "ICPCASIASG";
char G[MAXN][MAXN];
vecp adj[MAXN][MAXN];
pair dir[8] = {{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

bool dfs(int i, int j, int k){
    if(k == 9)
        return true;
    for(int z=0;z<adj[i][j].sz;z++){pair e = adj[i][j].ptr[z];
        int ii = e.first,
            jj = e.second;
        if(G[ii][jj] == T[k + 1] && dfs(ii, jj, k + 1))
            return true;
    }
    return false;
}
int main(){
    scanf("%d", &N);
    S = getstr();
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            G[i][j] = S[i * N + j];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            for(int k=0; k<8; k++){
                int ii = i + dir[k].first,
                    jj = j + dir[k].second;
                if(ii < 0 || ii >= N || jj < 0 || jj >= N)
                    continue;
                for(int m=0; m<9; m++)
                    if(G[i][j] == T[m] && G[ii][jj] == T[m + 1])
                        pbp(adj[i][j], newpair(ii, jj));
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(G[i][j] == 'I' && dfs(i, j, 0)){
                puts("YES");
                return 0;
            }
        }
    }
    puts("NO");
    return 0;
}
