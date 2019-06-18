#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

int vasprintf(char **str, const char *fmt, va_list args) {
  int size = 0;
  va_list tmpa;
  __builtin_va_copy(tmpa, args);
  size = vsnprintf(NULL, size, fmt, tmpa);
  __builtin_va_end(tmpa);
  if (size < 0) { return -1; }
  *str = (char *)malloc(size + 1);
  if (NULL == *str) { return -1; }
  size = vsprintf(*str, fmt, args);
  return size;
}
int asprintf(char **str, const char *fmt, ...) {
  int size = 0;
  va_list args;
  __builtin_va_start(args, fmt);
  size = vasprintf(str, fmt, args);
  __builtin_va_end(args);
  return size;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
///////////////////

int dp[1010][1010];
char*s1; int s1len;
char*s2; int s2len;

int dfs(int x, int y){
    if( x == s1len && y == s2len )
        return 0;
    if( dp[x][y] != -1 )
        return dp[x][y];
    int ans =(int)1e9;
    if( x < s1len)
        ans = min(ans, dfs(x+1, y) + 1);
    if( y < s2len )
        ans = min(ans, dfs(x, y+1) + 1);
    if( x < s1len && y < s2len && s1[x] == s2[y] )
        ans = min(ans, dfs(x+1, y+1) + 1);
    return dp[x][y] = ans;
}
void rec(int x,int y, char**r){
    if(x == s1len && y == s2len)
        return;
    int ans = (int)1e9;
    if(x < s1len){
        if( dfs(x+1, y) + 1 == dfs(x,y) ){
            *r = concatc(*r, s1[x]);
            rec(x+1, y, r);
            return;   
        }
    }
    if( y < s2len ){
        if( dfs(x, y+1) + 1 == dfs(x,y) ){
            *r = concatc(*r, s2[y]);
            rec(x, y+1, r);
            return;   
        }
    }
    if( x < s1len && y < s2len && s1[x] == s2[y] ){
        if( dfs(x+1, y+1) + 1 == dfs(x,y) ){
            *r = concatc(*r, s2[y]);
            rec(x+1, y+1, r);
            return;   
        }
    }
    return;
}
char*shortestCommonSupersequence(char*str1, char*str2){
    memset(dp, -1, sizeof(dp));
    s1 = str1; s1len = strlen(s1);
    s2 = str2; s2len = strlen(s2);
    char*r = strdup("");
    rec(0, 0, &r);
    return r;
}
// int main(){
//     
// }
