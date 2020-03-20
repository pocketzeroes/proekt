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
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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


typedef long long ll;
enum{MAXN = 200005};
int k, a[7];
int should_cover = 0;
vec hits[6];

ll dfs(int x, int msk){
    if(x==k)
        return(should_cover & msk) == should_cover;
    ll ret = 0;
    for(int z=0; z<hits[a[x]].sz; z++){int i=hits[a[x]].ptr[z];
        if(i&msk)
            continue;
        ret += dfs(x+1, i|msk);
    }
    return ret;
}
int main(){
    int n;
    scanf("%d %d", &n, &k);
    int already=0;
    for(int i=0; i<n; i++){
        char*s=getstr();
        for(int j=0; j<n; j++){
            if(s[j] == 'O')
                should_cover |= (1<<(i*n+j));
            if(s[j] == 'X')
                already |= (1<<(i*n+j));
        }
    }
    for(int i=0; i<k; i++)
        scanf("%d", &a[i]);
    for(int i=1; i<=n; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                if(j+i-1 < n){
                    int msk = 0;
                    for(int x=0; x<i; x++)
                        msk |= (1<<((j+x)*n+k));
                    pb(hits[i], msk);
                }
                if(i!=1 && k+i-1<n){
                    int msk = 0;
                    for(int x=0; x<i; x++)
                        msk |= (1<<(j*n+k+x));
                    pb(hits[i], msk);
                }
            }
        }
    }
    printf("%lld\n", dfs(0, already));
    return 0;
}
