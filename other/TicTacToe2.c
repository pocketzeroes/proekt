#include <stdio.h>

char g[3][4];

int i,j,k,m,n,N,xcount,ocount;

int win(char c){
   int i,j;
   for (i=0;i<3;i++) {
      for (j=0;j<3 && g[i][j]==c;j++);
      if (j==3) return 1;
      for (j=0;j<3 && g[j][i]==c;j++);
      if (j==3) return 1;
   }
   for (i=0;i<3 && g[i][i]==c;i++);
   if (i==3) return 1;
   for (i=0;i<3 && g[i][2-i]==c;i++);
   if (i==3) return 1;
   return 0;
}

main(){
   scanf("%d",&N);
   while (N--){
      scanf(" %s %s %s",g[0],g[1],g[2]);
      xcount = ocount = 0;
      for (i=0;i<3;i++) for (j=0;j<3;j++) {
         if (g[i][j] == 'X') xcount++;
         if (g[i][j] == 'O') ocount++;
      }
      if (
         ocount > xcount || xcount > ocount + 1
         || win('X') && win('O') 
         || win('O') && xcount != ocount
         || win('X') && xcount == ocount
      ) {
         printf("no\n");
         continue;
      }
      printf("yes\n");
   }
}
