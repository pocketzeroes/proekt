#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[1024*1024];
char*p  [1024*1024];
char cnt[1024];
char*prev;
int i,j,k,n,c,z,best,done;

int comp(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
int common (char *a, char *b){
   int i;
   for (i=0;a[i] && a[i] == b[i];i++);
   return i;
}
int main(){
   while (1 == scanf("%d",&n) && n){
      if (done++)
         printf("\n");
      for (i=k=0;i<n;i++){
         scanf("%s",buf+i*1024);
         for (j=0;buf[i*1024+j];j++){
            p[k++] = buf+i*1024+j;
         }
      }
      qsort(p, k, sizeof(char *), comp);
      memset(cnt, 0, sizeof(cnt));
      best = 0;
      for (i=j=c=0;i<k;){
         while (c <= n/2 && i<k){
            if (!cnt[(p[i++]-buf)/1024]++)
               c++;
         }
         while (c > n/2){
            if (!--cnt[(p[j++]-buf)/1024])
               c--;
         }
         if (j && common(p[j-1],p[i-1]) > best)
            best = common(p[j-1],p[i-1]); 
      }
      if (!best){
         printf("?\n");
         continue;
      }
      memset(cnt,0,sizeof(cnt));
      prev = "";
      for (i=j=c=0;i<k;){
         while (c <= n/2 && i<k){
            if (!cnt[(p[i++]-buf)/1024]++)
               c++;
         }
         while (c > n/2){
            if (!--cnt[(p[j++]-buf)/1024])
               c--;
         }
         if (j && common(p[j-1],p[i-1]) == best){
            if (strncmp(prev,p[j-1],best)){
               prev = p[j-1];
               for (z=0;z<best;z++)
                  printf("%c",p[j-1][z]);
               printf("\n");
            }
         }
      }
   }
   if (n)
      printf("missing input delimiter\n");
   return 0;
}
