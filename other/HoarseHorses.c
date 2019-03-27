#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

int N;
ll x1[1000], y_1[1000], x2[1000], y2[1000];
bool intersectionMatrix[1000][1000];
bool visited[1000];

int sgn(ll i){
  return(i > 0) ? 1 : ((i < 0) ? -1 : 0);
}
int direction(ll x1, ll y_1, ll x2, ll y2, ll x3, ll y3){
  return sgn((x2-x1)*(y3-y_1) - (y2-y_1)*(x3-x1));
}
bool onSegment(ll x1, ll y_1, ll x2, ll y2, ll x3, ll y3){
  return (min(x1,x2) <= x3 && max(x1,x2) >= x3 && min(y_1,y2) <= y3 && max(y_1,y2) >= y3);
}
bool doIntersect(int i, int j){
  int d1 = direction(x1[j], y_1[j], x2[j], y2[j], x1[i], y_1[i]);
  int d2 = direction(x1[j], y_1[j], x2[j], y2[j], x2[i], y2[i]);
  int d3 = direction(x1[i], y_1[i], x2[i], y2[i], x1[j], y_1[j]);
  int d4 = direction(x1[i], y_1[i], x2[i], y2[i], x2[j], y2[j]);
  if(d1 * d2 < 0 && d3 * d4 < 0)
    return true;
  if(d1 == 0 && onSegment(x1[j], y_1[j], x2[j], y2[j], x1[i], y_1[i]))
    return true;
  if(d2 == 0 && onSegment(x1[j], y_1[j], x2[j], y2[j], x2[i], y2[i]))
    return true;
  if(d3 == 0 && onSegment(x1[i], y_1[i], x2[i], y2[i], x1[j], y_1[j]))
    return true;
  if(d4 == 0 && onSegment(x1[i], y_1[i], x2[i], y2[i], x2[j], y2[j]))
    return true;
  return false;
}
void doVisit(int i){
  visited[i] = true;
  for(int j = 0; j < N; j++)
    if(visited[j] == false && intersectionMatrix[i][j] == true)
      doVisit(j);
}
int main(){
  scanf("%d", &N);
  ll sol = -N;
  for(int i = 0; i < N; i++){
    scanf("%lld %lld %lld %lld", &x1[i], &y_1[i], &x2[i], &y2[i]);
    visited[i] = false;
    intersectionMatrix[i][i] = false;
    for(int j = 0; j < i; j++){
      intersectionMatrix[i][j] = intersectionMatrix[j][i] = doIntersect(i,j);
      if(intersectionMatrix[i][j])
        sol++;
    }
  }
  for(int i = 0; i < N; i++){
    if(visited[i] == false){
      sol++;
      doVisit(i);
    }
  }
  printf("%lld\n", sol);
  return 0;
}

