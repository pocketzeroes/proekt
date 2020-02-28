#include<stdio.h>

double sum,r[100];
int i,j,k,m,n, R[100], prev[20001], who[20001];
char tmp[1000];

int main(){
   while (1 == scanf("%d",&n) && n) {
      for (i=0;i<n;i++) scanf("%lf",&r[i]);
      for (i=sum=0;i<n;i++) sum += r[i];
      for (i=0;i<n;i++) R[i] = r[i] * 20000/sum;
      memset(who,0,sizeof(who));
      memset(prev,0,sizeof(prev));
      who[0] = -1;
      for (i=0;i<n;i++) {
         for (j=10000;j>=0;j--) {
            if (!who[j]) continue;
            if (who[j+R[i]]) continue;
            who[j+R[i]] = i+1;
            prev[j+R[i]] = j;
         }
      }
      for (i=10000;!who[i];i--);
      while (i) {
         printf("%d ", who[i]);
         i = prev[i];
      }
      printf("\n");
   }
   if (n != 0) printf("missing end delimeter\n");
   return 0;
}
