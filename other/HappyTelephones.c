#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 10000};
enum{ maxm =   100};

int main (){
  int n, m;
  for (;;){
    scanf("%d %d", &n, &m);
    if (!n && !m)
      break;
    int source, dest, s[maxn], l[maxn], st, len;
    for (int i = 0; i < n; i++)
      scanf("%d %d %d %d", &source, &dest, &s[i], &l[i]);
    for (int i = 0; i < m; i++){
      scanf("%d %d", &st, &len);
      int overlaps = 0;
      for (int j = 0; j < n; j++)
        if (st + len > s[j] && st < s[j] + l[j]) 
          overlaps++; 
      printf("%d\n", overlaps);
    }             
  }
  return 0;
}
