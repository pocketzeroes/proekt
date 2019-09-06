#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXN=200000};
enum{ zrno=2500  };
enum{ h=80       };
int P[h+1][h+1];
int b[MAXN],c[MAXN];
int p[MAXN],ib[MAXN],ic[MAXN];
int n,x;

int pocet(int y, int z, int ii){
  int qy=y/zrno;
  int qz=z/zrno;
  int yy=qy*zrno;
  int zz=qz*zrno;
  int ret=0;
  for(int i=yy;i<y;i++) if(b[i]<ii) if(ic[b[i]]<z) ret++;
  for(int i=zz;i<z;i++) if(c[i]<ii) if(ib[c[i]]<yy) ret++;
  ret+=P[qy][qz];
  for(int i=qy+1;i<h;i++)
    for(int j=qz+1;j<h;j++) P[i][j]++;
  return ret;
}
int main(){
  for(;;) {
    scanf("%d",&n);
    if (!n) return 0;
    for(int i=0;i<n;i++){ scanf("%d",&x); x--; p[x]=i; }
    for(int i=0;i<n;i++){ scanf("%d",&b[i]); b[i]=p[b[i]-1]; ib[b[i]]=i; }
    for(int i=0;i<n;i++){ scanf("%d",&c[i]); c[i]=p[c[i]-1]; ic[c[i]]=i; }
    memset(P,0,sizeof(P));
    long long ret=0;
    for(int i=0;i<n;i++){
      ret+=pocet(ib[i],ic[i],i);
    }
    printf("%lld\n",ret);
  }
  return 0;
}
