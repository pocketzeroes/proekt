#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

char d [1000][32], used[1001];
int  i,j,k,m,n,c,tot,source,sink;
int  ar   [256],
     adj  [256][256], out[1000];
int  nused[256];
int  ad   [256][256];

void mark(char x){
   int i;
   for (i='a';i<='z';i++) {
      if (ad[x][i] > 0) {
         ad[x][i] = -1;
         mark(i);
      }
   }
}
int reachable(char x){
   int i,j;
   memcpy(ad,adj,sizeof(adj));
   mark(x);
   for (i='a';i<='z';i++) 
      for (j='a';j<='z';j++)
         if (ad[i][j] > 0) 
            return 0;
   return 1;
}
int main(){
   scanf("%d",&c);
   while (c--){
      if(1 != scanf("%d",&n))
         return printf("missing input\n")*0;
      memset(ar ,0,sizeof(ar) );
      memset(adj,0,sizeof(adj));
      tot = n-1;
      for (i=0;i<n;i++){
         if (1 != scanf("%s",d[i]))
            return printf("missing input\n")*0;
         ar[d[i][0]]--;
         ar[d[i][strlen(d[i])-1]]++;
         adj[d[i][0]][d[i][strlen(d[i])-1]]++;
      }
      qsort(d, n, 32, strcmp);
      for (source = 'a'; source <= 'z' && ar[source]>=0; source++);
      if (source > 'z')
         source = d[0][0];
      memset(used,0,sizeof(used));
      memset(nused,0,sizeof(nused));
      for (j=0;j<n;j++) {
         nused[source]++;
         for (i=0;i<n ;i++){
            if (used[i]) 
               continue;
            if (d[i][0] != source) 
               continue;
            adj[d[i][0]][d[i][strlen(d[i])-1]]--;
            if (reachable(d[i][strlen(d[i])-1])) 
               break;
            adj[d[i][0]][d[i][strlen(d[i])-1]]++;
         }
         if (i == n) 
            break;
         out[j] = i;
         source = d[i][strlen(d[i])-1];
         used[i] = 1;
      }
      if (j < n)
         printf("***\n");
      else {
         for (i=0;i+1<n;i++)
            printf("%s.",d[out[i]]);
         printf("%s\n",d[out[n-1]]);
      }
   }
   if (scanf("%s",d[0]) == 1)
      printf("extra input\n");
   return 0;
}
