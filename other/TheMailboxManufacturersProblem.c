#include <stdio.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#define MAX_CRACKERS (102)
#define MAX_MAILBOXES (10)
int tab[MAX_MAILBOXES][MAX_CRACKERS][MAX_CRACKERS];

void initTab(){
  int i,j,k,l;
  for (l=0;l<MAX_MAILBOXES;l++)
    for (i=0;i<MAX_CRACKERS;i++)
      for (j=i;j<MAX_CRACKERS;j++)
        tab[l][i][j] = (((j+1)*j)>>1)-(((i+1)*i)>>1);
  for (i=1;i<MAX_MAILBOXES;i++){
    for (j=0;j<MAX_CRACKERS;j++)
      for (k=0;k+j<MAX_CRACKERS;k++)
        for (l=1;l<j;l++)
          tab[i][k][k+j]= min(tab[i][k][k+j],k+l+max(tab[i-1][k][k+l-1],tab[i][k+l][k+j]));    
  }
}
int main(){
  int n,i,a,b;
  initTab();
  scanf("%d",&n);
  for (i=0;i<n;i++){
    scanf("%d %d",&a,&b);
    printf("%d\n",tab[a-1][0][b]);
  }
  return 0;
}
