#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

int t[((int)1e5) + 1];
int zeros[((int)1e5) + 1], ones[((int)1e5) + 1];

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  pair vp[m];
  for(int i = 0; i < m; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    a--;
    t[a]++;
    t[b]--;
    vp[i] = newPair(a, b);
  }
  for(int i = 0; i < (n); i++)
    t[i + 1] += t[i];
  for(int i = 0; i < (n); i++) {
    if (t[i] == 0)
      zeros[i + 1] = 1;
    else if (t[i] == 1)
      ones[i + 1] = 1;
  }
  for(int i = 0; i < (n); i++)
    zeros[i + 1] += zeros[i];
  for(int i = 0; i < (n); i++)
    ones[i + 1] += ones[i];
  for(int i = 0; i < m; i++){pair ab = vp[i];
    int ans = zeros[ab.first] - zeros[ab.second] + zeros[n];
    ans += ones[ab.second] - ones[ab.first];
    printf("%d\n", ans);
  }
  return 0;
}
