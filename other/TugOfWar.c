#include<stdio.h>
#include<stdlib.h>

int people[1000];
int i,j,k,n,tot,best;
char cando[101][50000];

int main(){
  scanf("%d",&n);
  for (i=0;i<n;i++) {
    scanf("%d",&people[i]);
    tot += people[i];
  }
  cando[0][0] = 1;
  for (i=0;i<n;i++){
    for (j=n/2;j>=0;j--) {
      for (k=45000;k>=0;k--){
        if (cando[j][k])
          cando[j+1][k+people[i]]=1;
      }
    }
  }
  for (i=0;i<=45000;i++){
    if (!cando[n/2][i])
      continue;
    if (abs(tot-2*i) < abs(tot-2*best))
      best = i;
  }
  if (best > tot-best)
    best = tot-best;
  printf("%d %d\n", best, tot-best);
  return 0;
}
