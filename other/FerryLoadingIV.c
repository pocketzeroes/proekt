#include<stdio.h>

int N,i,j,k,m,l,lp,rp,load,x[100000];
char b[100000][10];

int main(){
   scanf("%d",&N);
   while (N--) {
      k = 0;
      scanf("%d%d",&l,&m);
      for (i=0;i<m;i++){
         scanf("%d%s", &x[i], &b[i]);
      }
      lp=rp=k=0;  l*=100;
      for(;;){
         if (rp >= m && lp >=m)
            break;
         k++;
         load = 0;
         for(;lp<m;lp++){
            if (b[lp][0] != 'l')
               continue;
            if (load + x[lp] <= l)
               load += x[lp];
            else
               break;
         }
         if (rp >= m && lp >= m)
            break;
         k++;
         load = 0;
         for(;rp<m;rp++){
            if (b[rp][0] != 'r')
               continue;
            if (load + x[rp] <= l)
               load += x[rp];
            else
               break;
         }
      }
      printf("%d\n",k);  again:;
   }
   return 0;
}
