#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////
typedef long long ll;
enum{ inf=100000000};
int dr[4]={-1,1,0,0};
int dc[4]={0,0,-1,1};
bool vis [30][30];
int  dist[30][30];
bool forb[30][30];
vec adyx[30][30];
vec adyy[30][30];
vec cst [30][30];
int nr,nc;
int ncas=0;

bool okpos(int r,int c){
  return (r>-1&&r<nr&&c>-1&&c<nc);
}
bool ok(int r,int c){
  return (r>-1&&r<nr&&c>-1&&c<nc&&!vis[r][c]&&!forb[r][c]);
}
void ffill(int r,int c){
  if(!ok(r,c))
    return;
  vis[r][c]=1;
  if(r==nr-1&&c==nc-1)
    return;
  if(adyx[r][c].sz==0)
    for( ll k = 0; k < 4; k ++ )
      ffill(r+dr[k],c+dc[k]);
  for( ll k = 0; k < adyx[r][c].sz; k ++ )
    ffill(adyx[r][c].ptr[k],adyy[r][c].ptr[k]);
}
int main(){
  while(scanf("%d %d", &nc, &nr)==2 && (nc|nr)){
    ncas++;
    memset(vis, false, sizeof(vis));
    for( ll i = 0; i < nr; i ++)
      for( ll j = 0; j < nc; j ++)
        dist[i][j]=inf;
    dist[0][0]=0;
    for( ll i = 0; i < nr; i ++ )
      for( ll j = 0; j < nc; j ++ ){
        adyx[i][j].sz=0;
        adyy[i][j].sz=0;
        cst [i][j].sz=0;
      }
    memset(forb, false, sizeof(forb));
    int g;
    scanf("%d", &g);
    for( ll i = 0; i < g; i ++ ){
      int x, y;
      scanf("%d %d",&x,&y);
      forb[y][x]=true;
    }
    int e;
    scanf("%d", &e);
    for( ll i = 0; i < e; i ++ ){
      int x, y, x2, y2, e;
      scanf("%d %d %d %d %d",&x,&y,&x2,&y2,&e);
      adyx[y][x].ptr=pushback(adyx[y][x].ptr, &adyx[y][x].sz, y2);
      adyy[y][x].ptr=pushback(adyy[y][x].ptr, &adyy[y][x].sz, x2);
      cst [y][x].ptr=pushback(cst [y][x].ptr, &cst [y][x].sz, e );
    }
    ffill(0,0);
    for(ll i = 0; i < nr; i++)
      for(ll j = 0; j < nc; j++)
        if(!vis[i][j])
          forb[i][j]=true;
    int nit=0;
    for(;;){
      bool prv=false;
      int r,c;
      if(nit>=nr*nc+1)
        goto NEGLOOP;
      for( ll i = 0; i < nr; i ++ )
        for( ll j = 0; j < nc; j ++ ){
        r=i;c=j;
        if(forb[i][j])
          continue;
        if(i==nr-1&&j==nc-1)
          continue;
        if(adyx[r][c].sz==0)
        for( ll k = 0; k < 4; k ++ ){
          int ni=i+dr[k],nj=j+dc[k];
          if(!okpos(ni,nj))
            continue;
          if(!forb[ni][nj]){
            if(dist[ni][nj]>dist[i][j]+1){
              prv=true;
              dist[ni][nj]=dist[i][j]+1;
            }
          }
        }
        for( ll k = 0; k < adyx[r][c].sz; k ++ ){
          int ni=adyx[r][c].ptr[k],
              nj=adyy[r][c].ptr[k];
          if(!okpos(ni,nj))
            continue;
          if(!forb[ni][nj])
          if(dist[ni][nj]>dist[i][j]+cst[r][c].ptr[k]){
            prv=true;
            dist[ni][nj]=dist[i][j]+cst[r][c].ptr[k];
          }
        }
      }
      if(!prv)
        break;
      nit++;
    }
    if(forb[nr-1][nc-1]) {
      puts("Impossible");
      continue;
    }
    printf("%d\n", dist[nr-1][nc-1] );
    continue;
NEGLOOP:
    puts("Never");
  }
}
