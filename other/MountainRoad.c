#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

void solve(){
  int N, n[2] = {0, 0}, p[2] = {0, 0};
  int arr[2][250], len[2][250], fin[250][250][2];
  char s[9];
  scanf("%d", &N);
  for (int i = 0; i < N; ++i, ++n[*s-'A'])
    scanf("%s", s), scanf("%d%d", arr[*s-'A']+n[*s-'A'], len[*s-'A']+n[*s-'A']);
  memset(fin, 0x1f, sizeof(fin));
  for (int i = 0; i <= n[0]; p[p[1] = 0] = ++i)
    for (int j = 0; j <= n[1]; p[1] = ++j)
      for (int l = 0, s, t; l < 2; ++l, p[0] = i)
	for (s = t = i+j ? fin[i][j][1-l] : 0; p[l]++ < n[l]; s += 10, t += 10)
	  fin[p[0]][p[1]][l] = min(fin[p[0]][p[1]][l], t = max(t, (s = max(s, arr[l][p[l]-1]))+len[l][p[l]-1]));
  printf("%d\n", min(fin[n[0]][n[1]][0],fin[n[0]][n[1]][1]));
}
int main(){
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i)
    solve();
  return 0;
}
