#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int ls[100000],rs[100000];
bool notroot[100000];
int height[100000];
int ans[100000];
int N;

void doheight(int i){
  int h = 1;
  if (ls[i]){
    doheight(ls[i]-1);
    h = max(h,1+height[ls[i]-1]);
  }
  if (rs[i]){
    doheight(rs[i]-1);
    h = max(h,1+height[rs[i]-1]);
  }
  height[i] = h;
}
int getheight(int c){
  if (c)
    return height[c-1];
  else
    return 0;
}
void doans(int i, int lheight, int rheight, int ltopheight, int rtopheight){
  ans[i] = 0;
  ans[i] = max(ans[i],1+lheight);
  ans[i] = max(ans[i],1+rheight);
  ans[i] = max(ans[i],1+ltopheight+getheight(ls[i]));
  ans[i] = max(ans[i],1+rtopheight+getheight(rs[i]));
  if (ls[i])
    doans(ls[i]-1, lheight, max(rheight, 1+rtopheight+getheight(rs[i])), ltopheight, 1+rtopheight);
  if (rs[i])
    doans(rs[i]-1, max(lheight, 1+ltopheight+getheight(ls[i])), rheight, 1+ltopheight, rtopheight);
}
void doit(){
  scanf("%d", &N);
  if (N==0)
    exit(0);
  memset(notroot,0,sizeof(notroot));
  for(int i=(0);i<(N);++i){
    int l,r;
    scanf("%d%d", &l, &r);
    if (l)
      notroot[l-1] = 1;
    if (r)
      notroot[r-1] = 1;
    ls[i] = l;
    rs[i] = r;
  }
  int root = -1;
  for(int i=(0);i<(N);++i)
    if (!notroot[i])
      root = i;
  doheight(root);
  doans(root, 0, 0, 0, 0);
  for(int i=(0);i<(N);++i)
    printf("%d\n", ans[i]);
}
const int MULTICASE = 1;
int main() {
  do {
    doit();
  } while (MULTICASE);
}
