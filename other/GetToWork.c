#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
pair make_pair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

pair e [1024];
int arr[1024];
int ans[1024];

int main() {
    int K;
    scanf("%d", &K);
    for (int u = 1; u <= K; ++u){
        int N, T, E;
        scanf("%d%d%d", &N, &T, &E);
        int h, c;
        for (int i = 0; i < E; ++i){
            scanf("%d%d", &h, &c);
            --h;
            e[i] = make_pair(h, -c);
        }
        --T;
        qsort(e, E, sizeof(pair), cmpP);
        memset(arr, 0, sizeof(arr));
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < E; ++i) {
            if (e[i].first != T)
                ++arr[e[i].first];
        }
        for (int i = 0; i < E; ++i) {
            if (arr[e[i].first] > 0) {
                arr[e[i].first] += e[i].second;
                ++ans[e[i].first];
            }
        }
        bool can = true;
        for (int i = 0; i < E; ++i) {
            if (arr[e[i].first] > 0) 
                can = false;
        }
        if (can) {
            printf("Case #%d:", u);
            for (int i = 0; i < N; ++i)
                printf(" %d", ans[i]);
            printf("\n");
        }
        else {
            printf("Case #%d: IMPOSSIBLE\n", u);
        }
    }
    return 0;
}
