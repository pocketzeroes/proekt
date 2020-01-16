#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(pair a, pair b){
  if(a.first !=b.first )return(a.first <b.first )?-1:1;
  if(a.second!=b.second)return(a.second<b.second)?-1:1;
  return 0;
}
pair maxp(pair a,pair b){return cmpP(a,b)>0?a:b;}
pair minp(pair a,pair b){return cmpP(a,b)<0?a:b;}


int n,m;
pair p[1000];
int area(pair x, pair y, pair z){
  return (y.first-x.first)*(z.second-x.second)-(y.second-x.second)*(z.first-x.first);
}
bool on(pair x, pair y, pair z){
  if(area(x,y,z) != 0)
    return 0;
  return cmpP(minp(x,y), z)<=0&&
         cmpP(z, maxp(x,y))<=0;
}
double get(pair x, pair y, int z){
  return (double)((z-x.second)*y.first+(y.second-z)*x.first)/(y.second-x.second);
}
void test(pair z){
  int ans = 0;
  for (int i=0; i<(n); i++){
    pair x = p[i], y = p[(i+1)%n];
    if (on(x,y,z)){
      puts("on");
      return;
    }
    if (x.second > y.second)
      swap(x,y);
    if (x.second <= z.second && y.second > z.second){
      double t = get(x,y,z.second);
      if (t > z.first)
        ans++;
    }
  }
  if (ans % 2 == 1)
    puts("in");
  else
    puts("out");
}
void solve(){
  for(int i=0; i<n; i++)
    scanf("%d %d", &p[i].first, &p[i].second);
  scanf("%d", &m);
  for(int i=0; i<m; i++){
    pair z;
    scanf("%d %d", &z.first, &z.second);
    test(z);
  }
}
int main(){
  while(1){
    scanf("%d", &n);
    if(n==0)
      break;
    solve();
  }
  return 0;
}
