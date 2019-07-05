#include<stdio.h>
#include<math.h>
#include<stdbool.h>

int M, B, tm, tb;

bool go(int x, int t, int m, int b){
  if (m == M && b == B)
    return true;
  if (m != M && t+abs(x-m)+abs(m-M) > tm || b != B && t+abs(x-b)+abs(b-B) > tb)
    return false;
  if (m != M) {
    if (go(M, t + abs(x-m)+abs(m-M), M, b))
      return true;
    if (m != b && go(b, t + abs(x-m)+abs(m-b), b, b))
      return true;
  }
  if (b != B) {
    if (go(B, t + abs(x-b)+abs(b-B), m, B))
      return true;
    if (m != b && go(m, t + abs(x-b)+abs(b-m), m, m))
      return true;
  }
  return false;
}
int main(){
  int m, b;
  scanf("%d%d%d%d%d%d", &m, &b, &M, &B, &tm, &tb);
  printf("%s\n", go(0, 0, m, b) ? "possible" : "impossible");
  return 0;
}
