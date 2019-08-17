#include<stdio.h>
#include<stdlib.h>
int i,j,k,n;
int t[1000];
char cross[2000][16];
int nc,tot;

int compar(const void*pa, const void*pb){
   int*a=(int*)pa;
   int*b=(int*)pb;
   return *a - *b;
}
int main(){
   scanf("%d",&n);
   for(i=0;i<n;i++)
      scanf("%d", &t[i]);
   qsort(t, n, sizeof(int), compar);
   for(i=n-1;i>=3 && 2*t[1] < t[0]+t[i-1];i-=2){
      sprintf(cross[nc++], "%d %d\n",t[0],t[1]);
      sprintf(cross[nc++], "%d\n",t[0]);
      sprintf(cross[nc++], "%d %d\n",t[i-1],t[i]);
      sprintf(cross[nc++], "%d\n",t[1]);
      tot = tot + t[0]+2*t[1]+t[i];
   }
   for (;i>=2;i--){
      sprintf(cross[nc++],"%d %d\n",t[0],t[i]);
      sprintf(cross[nc++],"%d\n",t[0]);
      tot = tot + t[0] + t[i];
   }
   if (i==1){
      sprintf(cross[nc++],"%d %d\n",t[0],t[1]);
      tot = tot + t[1];
   }
   else{
      sprintf(cross[nc++],"%d\n",t[0]);
      tot = tot + t[0];
   }
   printf("%d\n",tot);
   for(i=0;i<nc;i++)
      printf("%s", cross[i]);
   return 0;
}
