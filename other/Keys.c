#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
int compP( pair a, pair b){
    if(a.first !=b.first )return(a.first <b.first )?-1:1;
    if(a.second!=b.second)return(a.second<b.second)?-1:1;
    return 0;
}
pair minP(pair a,pair b){return compP(a,b)<0?a:b;}
pair maxP(pair a,pair b){return compP(a,b)>0?a:b;}


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

enum{ N = 60};
int n , m , ca;
char str[10];
int cnt[N][2];
vec e[N];
bool vaild[N] , vis[N];
pair res;
int f[N][3];
int X , Y;

void DFS(int x , int fa){
    vis[x] = 1;
    if (!cnt[x][0] && !cnt[x][1])
        f[x][2] = 0;
    if (!cnt[x][1])
        f[x][0] = 0;
    if (!cnt[x][0])
        f[x][1] = 0;
    for(int z=0; z<e[x].sz; z++){int y = e[x].ptr[z];
        if (y != fa) {
            DFS(y , x);
            f[x][0] += min(f[y][0] , min(f[y][1] + 2 , f[y][2] + 1));
            f[x][1] += min(f[y][1] , min(f[y][0] + 2 , f[y][2] + 1));
            f[x][2] += min(f[y][0] + 2 , min(f[y][1] + 2 , f[y][2]));
        }
    }
}
void dfs(int k , int sum , int*s0 , int*s1){
    if (sum > res.first)
        return;
    if (X == 26 && *s0) 
        return;
    if (Y == 26 && *s1) 
        return;
    if (k == 26) {
        memset(f , 0x3f , sizeof(f));
        memset(vis , 0 , sizeof(vis));
        int ret = 0;
        for (int x = 0 ; x < 26 ; ++ x)
            if (vaild[x] && !vis[x]) {
                DFS(x , 0);
                ret += min(f[x][2] , min(f[x][0] , f[x][1]) + 1);
            }
        res = minP(res , newPair(sum , ret));
    }
    else {
        if (!vaild[k])
            dfs(k + 1, sum, s0, s1);
        else {
            int mn = min(cnt[k][0] , cnt[k][1]);
            if (cnt[k][0] == 0 && cnt[k][1] == 0) {
                dfs(k + 1 , sum, s0, s1);
            }
            else {
                if (cnt[k][0] == mn) {
                    (*s0) += mn;
                    cnt[k][0] -= mn;
                    dfs(k + 1 , sum + mn, s0, s1);
                    cnt[k][0] += mn;
                    (*s0) -= mn;
                }
                if (cnt[k][1] == mn) {
                    (*s1) += mn;
                    cnt[k][1] -= mn;
                    dfs(k + 1 , sum + mn, s0, s1);
                    cnt[k][1] += mn;
                    (*s1) -= mn;
                }
            }
        }
    }
}
void work(){
    int i , x , y;
    int t0 = 0 , t1 = 0;
    memset(cnt , 0 , sizeof(cnt));
    for (i = 0 ; i < 26 ; ++ i)
        e[i].sz=0;
    memset(vaild , 0 , sizeof(vaild));
    do {
        char u = str[0] , v = str[1];
        if(u > v)
          swap(u , v);
        if (islower(u)) {
            vaild[u - 'a'] = vaild[v - 'a'] = 1;
            e[u-'a'].ptr = pushback(e[u-'a'].ptr, &e[u-'a'].sz, v-'a');
            e[v-'a'].ptr = pushback(e[v-'a'].ptr, &e[v-'a'].sz, u-'a');
        }
        else {
            vaild[v - 'a'] = 1;
            if (u <= 'M') {
                ++ cnt[v - 'a'][0];
                if (!t0)
                    ++ t0;
            }
            else {
                ++ cnt[v - 'a'][1];
                if (!t1)
                    ++ t1;
            }
        }
    }
    while (scanf("%s" , str) , *str != '0');
    res = newPair(1 << 30 , 1 << 30);
    for (X = 0 ; X <= 26 ; ++ X)
        for (Y = 0 ; Y <= 26 ; ++ Y) {
            if (X != 26 && X == Y) 
                continue;
            if (X < 26 && !vaild[X]) 
                continue;
            if (Y < 26 && !vaild[Y]) 
                continue;
            int a0 = cnt[Y][0] , a1 = cnt[X][1];
            cnt[Y][0] -= a0 , cnt[X][1] -= a1;
            cnt[X][0] += a0 , cnt[Y][1] += a1;
            dfs(0 , a0 + a1 , &cnt[X][0] , &cnt[Y][1]);
            cnt[Y][0] += a0 , cnt[X][1] += a1;
            cnt[X][0] -= a0 , cnt[Y][1] -= a1;
        }
    printf("Case %d: " , ++ ca);
    if (res.first == 1 << 30)
        puts("impossible");
    else{
        printf("%d %d\n" , res.first + res.first , res.second - t0 - t1);
    }
}
int main(){
    while (~scanf("%s" , str))
        work();
    return 0;
}
