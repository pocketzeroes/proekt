#include <stdio.h>
enum{ MAXD = 10};
enum{ MAXF =  5};
static char mz[MAXD][MAXD];
static int n, w, h;
static int vis[MAXD][MAXD];
static int cnt, sum, nbr;

struct orientation{
  int x,y;
};
static struct orientation rel[MAXF];

int seen(int y,int x){
  if (x<0 || x>=w || y<0 || y>=h)
    return 1;
  else
    return (vis[y][x]!=0) || (mz[y][x] != 'X');
}
static int cnt;
static void dfs(int x,int y,int ant){
	int i,iseen = 0;
	for (i=0;i<ant && !iseen;i++) {
		iseen|=seen(rel[i].y+y,rel[i].x+x);
	}
	if (!iseen) {
		for (i=0;i<ant;i++) {
			if (!vis[rel[i].y+y][rel[i].x+x])
				vis[rel[i].y+y][rel[i].x+x] = i+1;
			else
				return;
		}
		cnt++;
		dfs(x+1,y,ant);
		dfs(x,y+1,ant);
		dfs(x-1,y,ant);
		dfs(x,y-1,ant);
	}
}
int explore(int ant){
  int x,y;
  for (y=0;y<h;y++)
    for (x=0;x<w;x++)
      vis[y][x] = 0;
  cnt = 0;
  dfs(0,0,ant);
  return cnt;
}
int search(int ys,int xs,int k){
  int x,y,found = 0;
  if (k==0) {
    int cnt = explore(nbr);
    found = cnt*nbr == sum;
  }
  else {
    for (y=ys;y<h && !found;y++)
      for (x=(y==ys?xs:0);x<w && !found;x++)
        if (mz[y][x]=='X') {
          rel[nbr-k].y = y;
          rel[nbr-k].x = x;
          if (explore(nbr-k+1)*nbr>=sum)
            found = search(y,x+1,k-1);
          if (k==nbr) 
            return found;
        }
  }
  return found;
}
int search_factors(){
  int k, found = 0;
  for (k=2;k<MAXF+1 && !found;k++) {
    if (sum % k == 0) {
      nbr = k;
      found = search(0,0,k);
    }
  }
  return found;
}
int main(){
  int x,y;
  int iter = 0;
  scanf("%d %d\n",&h,&w);
  sum = 0;
  for (y=0;y<h;y++) {
    for (x=0;x<w;x++){
      scanf("%c",&mz[y][x]);
      sum += mz[y][x]=='X';
    }
    scanf("\n");
  }
  if (search_factors()){
    for (y=0;y<h;y++){
      for (x=0;x<w;x++) {
        printf("%c",vis[y][x]?(char)(48+vis[y][x]):'.');
      }
      printf("\n");
    }
  }
  else {
    printf("No solution\n");
  }
  return 0;
}
