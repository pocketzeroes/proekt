#include<stdio.h>

enum{ MAXNODES = 500};

struct tnode{
  int c,d,tid,fromwho;
};

static struct tnode nodes[MAXNODES];
static int    nreach     [MAXNODES];
static int    reachs     [MAXNODES][MAXNODES];
static int    path       [MAXNODES];
static int    vis        [MAXNODES];

int augment(int who, int cnt){
  int i,rcnt;
  if (!vis[who]){
    vis[who]=1;
    for (i=0;i<nreach[who];i++){
      int con=nodes[reachs[who][i]].fromwho;
      path[cnt]=reachs[who][i];
      if (con==-1)
        return cnt+1;
      rcnt=augment(con,cnt+1);
      if (rcnt)
        return rcnt;
    }
  }
  return 0;
}
int main(){
  int n,i,j,k,a,b,h,m,p,cur,cabs,tid;
  scanf("%d",&n);
  while (n--){
    scanf("%d",&p);
    for (i=0;i<p;i++){
      scanf("%d:%d %d %d %d %d",&h,&m,&a,&b,&nodes[i].c,&nodes[i].d);
      tid=h*60+m;
      nodes[i].tid=tid+abs(a-nodes[i].c)+abs(b-nodes[i].d);
      nodes[i].fromwho=-1;
      nreach[i]=0;
      for (j=0;j<i;j++){
        int arrtid=nodes[j].tid+abs(nodes[j].c-a)+abs(nodes[j].d-b);
        if (arrtid<tid)
          reachs[j][nreach[j]++]=i; 
      }
    }
    cabs=0;
    for (i=0;i<p;i++){
      for (j=0;j<p;j++)
        vis[j]=0;
      k=augment(i,0);
      cabs+=(!k);
      cur=i;
      for (j=0;j<k;j++){
        int tmp=nodes[path[j]].fromwho;
        nodes[path[j]].fromwho = cur;
        cur=tmp;
      }
    }
    printf("%d\n",cabs);
  }
  return 0;
}
