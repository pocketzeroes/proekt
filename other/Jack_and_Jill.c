#include <stdio.h>
#include <string.h>
#include <math.h>
enum{
 N = 0,
 S = 1,
 E = 2,
 W = 3
};
char g[100][101], jack[10000], jill[10000];
int i,j,k,m,n,Hi,Hj,Si,Sj,hi,hj,si,sj,qn;
int cnt,a,b,i,j,qi,I,J,hi,lo,mid,min2;
double bestd;

struct qq{
   char I,J,i,j;
   int d;
   int prev;
   int link;
}q[1000000];

int fst[20000], lst[20000], qh, here;

char done[30][30][30][30];

#define isdone(a,b,c,d) done[a][b][c][d]
#define setdone(a,b,c,d) (done[a][b][c][d] = 1)

void dump(int z){
   if (z == 0)
      return;
   dump(q[z].prev);
   if (q[q[z].prev].I < q[z].I) strcat(jack,"S");
   if (q[q[z].prev].I > q[z].I) strcat(jack,"N");
   if (q[q[z].prev].J < q[z].J) strcat(jack,"E");
   if (q[q[z].prev].J > q[z].J) strcat(jack,"W");
   if (q[q[z].prev].i < q[z].i) strcat(jill,"S");
   if (q[q[z].prev].i > q[z].i) strcat(jill,"N");
   if (q[q[z].prev].j < q[z].j) strcat(jill,"E");
   if (q[q[z].prev].j > q[z].j) strcat(jill,"W");
}
int main(){
   while (1 == scanf("%d",&n) && n) {
      for (i=0;i<n;i++)
         scanf("%s",g[i]);
      jack[0] = jill[0] = 0;
      bestd = 0;
      for (i=0;i<n;i++)
         for (j=0;j<n;j++) {
            if (g[i][j] == 'H') {q[0].I = i; q[0].J = j;}
            if (g[i][j] == 'h') {q[0].i = i; q[0].j = j;}
         }
      memset(done,0,sizeof(done));
      memset(fst,-1,sizeof(fst) );
      memset(lst ,0,sizeof(lst) );
      q[0].d = (q[0].I-q[0].i)*(q[0].I-q[0].i)+ (q[0].J-q[0].j)*(q[0].J-q[0].j);
      q[0].link = -1;
      fst[q[0].d] = lst[q[0].d] = 0;
      here = 20000;
      qi = -1;
      qn = 1;
      for (qh=0;qh<qn;qh++,qi=q[qi].link){
         if (qi == -1) {
            while(fst[--here] == -1);
            qi = fst[here];
         }
         for (a=0;a<4;a++)
          for (b=0;b<4;b++){
            I = q[qi].I; J = q[qi].J; i = q[qi].i; j = q[qi].j;
            if (g[I][J] == 'S') { }
            else if (a == N) I--;
            else if (a == S) I++;
            else if (a == W) J--;
            else if (a == E) J++;
            if (g[i][j] == 's') { }
            else if (b == N) i--;
            else if (b == S) i++;
            else if (b == W) j--;
            else if (b == E) j++;
            if (I<0 || J<0 || i<0 || j<0 || I == n || J == n || i == n || j == n)
               continue;
            if (g[I][J] == '*' || g[I][J] == 'h' || g[I][J] == 's')
               continue;
            if (g[i][j] == '*' || g[i][j] == 'H' || g[i][j] == 'S')
               continue;
            if (isdone(I,J,i,j))
               continue;
            q[qn].d = (I-i)*(I-i) + (J-j)*(J-j);
            if (q[qi].d < q[qn].d)
               q[qn].d = q[qi].d;
            setdone(I,J,i,j);
            q[qn].I = I; q[qn].J = J; q[qn].i = i; q[qn].j = j; q[qn].prev = qi;
            if (fst[q[qn].d] == -1)
               fst[q[qn].d] = lst[q[qn].d] = qn;
            else{
               q[lst[q[qn].d]].link = qn;
               lst[q[qn].d] = qn;
            }
            q[qn].link = -1;
            if (g[I][J] == 'S' && g[i][j] == 's')
               goto dun;
            qn++;
          }
      }
      printf("oops!\n");
 dun: jack[0] = jill[0] = 0;
      dump(qn);
      bestd = sqrt(q[qn].d);
      if (cnt++)
         printf("\n");
      i = strlen(jack);
      j = strlen(jill);
      if (j > i)
          i = j;
      i = 9 * 60 - i;
      printf("%0.2lf\n%s\n%s\n",bestd,jack,jill);
   }
   if(n)
      printf("missing 0 in input\n");
   return 0;
}
