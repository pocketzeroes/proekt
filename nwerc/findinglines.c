#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
	ll x, y;
}point;

point newpoint(ll x, ll y){
  point rez;
  rez.x = x;
  rez.y = y;
  return rez;
}
point operatorSub(point a, point b){
  return newpoint(a.x-b.x, a.y-b.y);
}
ll cross(point a, point b){
  return a.x*b.y - a.y*b.x;
}

int n, p;
point P[1<<20];

bool check(){
	if (n < 3) 
    return true;
	for (int i = 0; i < 250; ++i) {
		int a = rand() % n, b = rand() % n, c = 0;
		if (a == b) 
      continue;
		for (int j = 0; j < n; ++j){
      point diff = operatorSub(P[j], P[a]);
      point minus= operatorSub(P[b], P[a]);
			c += !cross(diff, minus);
    }
		if (100*c >= p*n) 
      return true;
	}
	return false;
}
int main(void) {
	scanf("%d %d", &n, &p);
	for (int i = 0; i < n; ++i) 
    scanf("%d %d", &P[i].x, &P[i].y);
	printf("%spossible\n", check() ? "" : "im");
	return 0;
}
























































