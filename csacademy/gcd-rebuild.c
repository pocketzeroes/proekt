#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int gcd(int u, int v ){
  return v != 0?gcd(v, u%v):u;
}
int lcm(int q, int w){
  return q / gcd(q, w) * w;
}

int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  int v[n]; fill(v, n, 1); 
  int u[m]; fill(u, m, 1);
  int a[n][m];
  enum{ INF = 1000000000};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
      v[i] = lcm(v[i], a[i][j]);
      if (v[i] > INF)
        return puts("-1")*0;
      u[j] = lcm(u[j], a[i][j]);
      if (u[j] > INF)
        return puts("-1")*0;
    }
  }
  for (int i = 0; i < n; ++i){
    for (int j = 0; j < m; ++j){
      if (a[i][j] != gcd(v[i], u[j]))
        return puts("-1")*0;
    }
  }
  for (int i = 0; i < n; ++i)
    printf("%d%c", v[i], " \n"[i + 1 == n]);
  for (int i = 0; i < m; ++i)
    printf("%d%c", u[i], " \n"[i + 1 == m]);
}






















































