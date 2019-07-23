#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n, W;
int gl[1005], rr[1005];
int solve(int its){
	int t=0, x=0;
	static int pos[1005], dir[1005];
	for (int i=0; i<n; i++)
    pos[i]=gl[i], dir[i]=1;
	if(its==-1)
    its = 10*W*W;
	while (x < W && t < its){
		static bool fwd[1005];
    memset(fwd,0,sizeof fwd);
		for (int i=0; i<n; i++){
			int nxt = pos[i]+dir[i];
			if (dir[i]==1)
        fwd[pos[i]] = true;
			if(nxt==gl[i]||nxt==rr[i])
        dir[i]*=-1;
			pos[i]=nxt;
		}
		if (fwd[x])
      x++;
    else if (!fwd[x-1])
      x--;
		t++;
	}
	if (x == W)
    return t;
  else
    return -1;
}
int main(){
	int T;
  scanf("%d", &T);
	for(int tc=1; tc<=T; tc++){
		scanf("%d %d", &n, &W);
		for (int i=0; i<n; i++)
      scanf("%d %d", &gl[i], &rr[i]);
		int ans = solve(10*W*W);
		if (ans == -1)
      puts("IMPOSSIBLE");
    else
      printf("%d\n",ans);
	}
  return 0;
}
