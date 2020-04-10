#include<stdio.h>
#include<string.h>
int m,n,i,j,k,p,tot;
int d[21][21], e;
int cost[1<<20+1];

int match(int e){
  int i,j,k,best=0x7fffffff;
  if(!e)
    return 0;
  if(cost[e] != 0)
    return cost[e];
  for(i=1;!(e & (1<<i));i++);
  for(j=i+1;j<=n;j++){
    if(!(e & (1<<j)))
      continue;
    k = match(e - (1<<i) - (1<<j));
    if(d[i][j] + k < best)
      best = d[i][j] + k;
  }
  return cost[e] = best;
}
int main(){
  while(2 == scanf("%d%d",&n,&m)){
    for(i=1;i<=n;i++)
      for(j=1;j<=n;j++)
        d[i][j] = (i!=j) * 0x3fffffff;
    memset(cost,0,sizeof(cost));
    e   = 0;
    tot = 0;
    for(i=0;i<m;i++){
      scanf("%d %d %d", &j, &k, &p);
      if(p < d[j][k])
        d[j][k] = d[k][j] = p;
      tot += p;
      e ^= (1<<j);
      e ^= (1<<k);
    }
    for(i=1;i<=n;i++)
      for(j=1;j<=n;j++)
        for(k=1;k<=n;k++){
          if(d[j][i]+d[i][k] < d[j][k])
            d[j][k] = d[j][i]+d[i][k];
    }
    printf("%d\n", tot+match(e));
  }
  if(n)
    printf("input data missing end delim\n");
  return 0;
}
