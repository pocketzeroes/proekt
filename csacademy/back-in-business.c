#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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
///////////////////////////////////////////
enum{ MAXN =(int)1e3};
int di[4]={1, 0, -1, 0};
int dj[4]={0, 1, 0, -1};
int n, m, d[MAXN][MAXN], si, sj, fi, fj;
vecp tv[2*MAXN];
bool vis[MAXN][MAXN];

int main(){
    memset(d, 0x3f, sizeof(d));
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; ++i){
        char*s = getstr();
        for(int j=0; j<m; ++j){
            if(s[j]=='S'){
                si=i;
                sj=j;
            }
            else if(s[j]=='F'){
                fi=i;
                fj=j;
            }
            else if(s[j]=='P'){
                d[i][j]=0;
            }
            if(j)
                d[i][j] = min(d[i][j], d[i][j-1]+1);
        }
        for(int j=m-2; ~j; --j)
            d[i][j]=min(d[i][j], d[i][j+1]+1);
    }
    for(int i=1; i<n; ++i){
        for(int j=0; j<m; ++j) {
            d[i][j]=min(d[i-1][j]+1, d[i][j]);
        }
    }
    for(int i=n-2; ~i; --i){
        for(int j=0; j<m; ++j){
            d[i][j]=min(d[i+1][j]+1,d[i][j]);
        }
    }
    tv[d[si][sj]].ptr = pushbackP(tv[d[si][sj]].ptr, &tv[d[si][sj]].sz, (pair){si,sj});
    vis[si][sj]=1;
    for(int md=2*n-1; md; --md){
        for(int it=0; it<tv[md].sz; ++it){
            pair u = tv[md].ptr[it];
            if(u.first == fi && u.second == fj){
                printf("%d", md);
                return 0;
            }
            for(int k=0; k<4; ++k) {
                int ni=u.first +di[k],
                    nj=u.second+dj[k];
                if(ni<0||ni>=n||nj<0||nj>=m||vis[ni][nj])
                    continue;
                vis[ni][nj]=1;
                tv[min(md,d[ni][nj])].ptr = pushbackP(tv[min(md,d[ni][nj])].ptr, &tv[min(md,d[ni][nj])].sz,(pair){ni,nj});
            }
        }
    }
    puts("impossible");
    return 0;
}
