#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 300*300+10};
int sum = 0;
bool isCrack[N], visited[301][301][301];
int n, c1, c2, c3;

bool dfs(int cnt1, int cnt2, int cnt3){
  int Dist = cnt1+2*cnt2+3*cnt3;
  if(Dist == sum) 
    return true;
  if(Dist > sum) 
    return false;
  if(isCrack[Dist]) 
    return false;
  visited[cnt1][cnt2][cnt3] = true;
  if(cnt1+1 <= c1 && !visited[cnt1+1][cnt2][cnt3] && dfs(cnt1+1, cnt2, cnt3))
    return true;
  if(cnt2+1 <= c2 && !visited[cnt1][cnt2+1][cnt3] && dfs(cnt1, cnt2+1, cnt3))
    return true;
  if(cnt3+1 <= c3 && !visited[cnt1][cnt2][cnt3+1] && dfs(cnt1, cnt2, cnt3+1))
    return true;
  return false;
}
int main(){
  scanf("%d %d %d %d", &n, &c1, &c2, &c3);
  for(int i=0; i<n; ++i){
    int len;
    scanf("%d", &len);
    sum += len;
    isCrack[sum] = true;
  }
  if(dfs(0,0,0))
    puts("YES");
  else 
    puts("NO");
  return 0;
}
