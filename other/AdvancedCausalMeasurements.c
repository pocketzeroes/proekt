#include<stdio.h>
#include<stdlib.h>
#include<math.h>

enum{BUFFSZ=1000000};
int n, m, i, j, k, c, cases,
    x[BUFFSZ],
    y[BUFFSZ],
    l[BUFFSZ],
    r[BUFFSZ],
    d[BUFFSZ];
int hi, lo, mid, cookie;

int test(int dd){
   int i, rr=0;
   ++cookie;
   for (i=j=0;i<n;i++) {
      if (d[l[i]] == cookie)
          continue;
      rr++;
      int xx = x[l[i]]+y[l[i]]+dd;
      for (;j<n && x[r[j]]-y[r[j]] <= xx;j++) {
         d[r[j]] = cookie;
      }
      if (j >= n)
          break;
   }
   return rr;
}
int compl(const void*pa, const void*pb){
   int*a=(int*)pa;
   int*b=(int*)pb;
   return (x[*a]+y[*a]) - (x[*b]+y[*b]);
}
int compr(const void*pa, const void*pb){
   int*a=(int*)pa;
   int*b=(int*)pb;
   return (x[*a]-y[*a]) - (x[*b]-y[*b]);
}
int main(){
   scanf("%d",&cases);
   for (c=1; c <= cases; c++) {
      int miny = 2000000;
      scanf("%d%d",&n,&m);  
      for (i=0;i<n;i++) {
         scanf("%d%d",&y[i],&x[i]);
         l[i] = r[i] = i;
         if (y[i] < miny) miny = y[i];
      }
      qsort(l,n,sizeof(int),compl);
      qsort(r,n,sizeof(int),compr);
      lo = -miny*2+1;
      hi = 4000000;
      while (hi >= lo){
         mid = (hi+lo)/2;
         if (test(mid) > m)
             lo = mid+1;
         else
             hi = mid-1;
      }
      if (test(hi) <= m)
          lo = hi;
      printf("Case %d: %0.0lf\n",c,floor(lo/-2.0+.00000001));
   }
   return 0;
}
