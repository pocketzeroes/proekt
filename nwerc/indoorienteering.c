#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ nmax = 14};
ll Dis[nmax][nmax];
ll Trip1[720], Trip2[720];


/////////////////////////
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}
/////////////////////////

int tryallperms(int n, int p, int s, ll*Trip){
  if (s == 0){
    Trip[0] = Dis[0][p];
    return 1;
  }
  int m = 0, i, k = 0;
  int Point[nmax/2];
  ll d = 0;
  for (i = 1; i < n; i++)
    if (s & (1<<i))
      Point[k++] = i;
  do{ 
    d = Dis[0][Point[0]];
    for (i = 1; i < k; i++)
      d += Dis[Point[i-1]][Point[i]];
    d += Dis[Point[k-1]][p];
    Trip[m++] = d;
  }
  while(next_permutation(Point, k));
  return m;
}
int main(){
  int n, i, j, m1, m2, p, q, s;
  ll L;
  scanf("%d %lld", &n, &L);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      scanf("%lld", &Dis[i][j]);
  for (p = 1; p < n; p++){
    q = (p==1 ? 2 : 1); 
    for (s = 0; s < (1<<n); s += 2)
      if (!(s & (1<<p)) && !(s & (1<<q)) && __builtin_popcount(s) == n/2-1){
        m1 = tryallperms(n, p, s, Trip1);
        m2 = tryallperms(n, p, s ^ ((1<<n)-2) ^ (1<<p), Trip2);
        for (i = 0; i < m1; i++)
          for (j = 0; j < m2; j++)
            if (Trip1[i] + Trip2[j] == L){
              printf("possible\n");
              return 0;
            }
      }
  }
  printf("impossible\n");
  return 0;
}










