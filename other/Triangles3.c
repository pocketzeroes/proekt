#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
#define reverse(nums, start, end) do{      \
    while(start < end){                    \
        swap(nums[start], nums[end]);      \
        start++;                           \
        end--;                             \
    }                                      \
}while(0)

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char*getstr(){
  char line[2000];
  fgets(line, 2000, stdin);
  return strdup(line);
}
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

int f[66666];

inline int lowbit(int s){
    return s & (-s);
}
inline void modify(int i, int x, int n){
    while (i <= n)
        f[i] += x, i += lowbit(i);
}
inline int query(int i){
    int ret = 0;
    while (i > 0)
        ret += f[i], i -= lowbit(i);
    return ret;
}
vec del[66666];

int main(){
    int r, c;
    scanf("%d %d", &r, &c);
    r = 2 * r - 1,
    c = 2 * c - 1;
    char*s[r];
    getchar();
    for(int i=0; i<r; ++i){
        s[i] = calloc(c, sizeof(char));
        memset(s[i], ' ', c);
        for(int j=0; j<c; ++j){
            s[i][j]=getchar();
            if(s[i][j]=='\n'){
               s[i][j] = ' ';
               goto here;
            }
        }
        getchar();
   here:;
    }
    ll ans=0;
    for(int rot=0; rot<2; ++rot){
        int R [r][c]; memset(R ,0,sizeof(R ));
        int UL[r][c]; memset(UL,0,sizeof(UL));
        int UR[r][c]; memset(UR,0,sizeof(UR));
        for(int j = c - 1; j >= 0; --j){
            if(s[0][j] != 'x')
                continue;
            int maxi = fmin((r - 1) / 2, (c - 1 - j) / 2) + 1;
            for(int ii = 0, jj = j; ii < r && jj < c; ii += 2, jj += 2){
                if(jj + 2 < c && s[ii][jj + 2] != ' ')
                    R[ii][jj] = R[ii][jj + 4] + 1;
                if(ii >= 2 && jj >= 2 && s[ii - 1][jj - 1] != ' ')
                    UL[ii][jj] = UL[ii - 2][jj - 2] + 1;
                if(ii >= 2 && jj + 2 < c && s[ii - 1][jj + 1] != ' ')
                    UR[ii][jj] = UR[ii - 2][jj + 2] + 1;
                ans += query(ii / 2 + 1) - query(ii / 2 - fmin(UL[ii][jj], UR[ii][jj]));
                if(R[ii][jj]){
                    modify(ii / 2 + 1, 1, maxi);
                    int q=fmin(ii/2+1+R[ii][jj],maxi);
                    del[q].ptr = pushback(del[q].ptr, &del[q].sz, ii / 2 + 1);
                }
                for(int z=0;z<del[ii/2+1].sz;z++){int x = del[ii/2+1].ptr[z];
                    modify(x, -1, maxi);
                }
                del[ii / 2 + 1].sz=0;
            }
        }
        for(int i = 1; i < r; i++){
            if(s[i][0] != 'x')
                continue;
            int maxj = fmin((r - 1 - i) / 2, (c - 1) / 2) + 1;
            for(int ii = i, jj = 0; ii < r && jj < c; ii += 2, jj += 2){
                if(jj + 2 < c && s[ii][jj + 2] != ' ')
                    R[ii][jj] = R[ii][jj + 4] + 1;
                if(ii >= 2 && jj >= 2 && s[ii - 1][jj - 1] != ' ')
                    UL[ii][jj] = UL[ii - 2][jj - 2] + 1;
                if(ii >= 2 && jj + 2 < c && s[ii - 1][jj + 1] != ' ')
                    UR[ii][jj] = UR[ii - 2][jj + 2] + 1;
                ans += query(jj / 2 + 1) - query(jj / 2 - fmin(UL[ii][jj], UR[ii][jj]));
                if(R[ii][jj]){
                    modify(jj / 2 + 1, 1, maxj);
                    int q=fmin(jj / 2 + 1 + R[ii][jj], maxj);
                    del[q].ptr = pushback(del[q].ptr, &del[q].sz, jj/2+1);
                }
                for(int z=0;z<del[jj/2+1].sz;z++){int x = del[jj/2+1].ptr[z];
                    modify(x, -1, maxj);
                }
                del[jj / 2 + 1].sz=0;
            }
        }
        int starti = 0;
        int endi   = r-1;
        reverse(s, starti, endi);
    }
    printf("%lld\n", ans);
    return 0;
}
