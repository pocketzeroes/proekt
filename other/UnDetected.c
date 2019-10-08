#pragma GCC optimize "-O3"
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
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define sqr(x) ((x) * (x))

int n;
int m[201][301];

int q_head, q_tail;
pair q[1000000];

int main(){
    scanf("%d", &n);
    int i;
    for(i = 0; i < n; ++i){
        int x, y, r;
        scanf("%d%d%d", &x, &y, &r);
        q_head = 0;
        q_tail = 0;
        for (int xx = 0; xx <= 200; ++xx)
            q[q_tail++] = (pair){xx, 0};
        bool ok = false;
        while (q_head != q_tail) {
            pair p = q[q_head++];
            if(m[p.first][p.second] != i)
                continue;
            if(sqr(p.first - x) + sqr(p.second - y) <= sqr(r))
                continue;
            m[p.first][p.second] = i + 1;
            if (p.second == 300)
                ok = true;
            if (p.second < 300)
                q[q_tail++] = (pair){p.first, p.second + 1};
            if (p.second > 0)
                q[q_tail++] = (pair){p.first, p.second - 1};
            if (p.first < 200)
                q[q_tail++] = (pair){p.first + 1, p.second};
            if (p.first > 0)
                q[q_tail++] = (pair){p.first - 1, p.second};
        }
        if (!ok)
            break;
    }
    printf("%d\n", i);
    return 0;
}
