#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
typedef struct{
    int first;
    int second;
}pair;
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

#define fs first
#define sc second
int b;
pair a[111111];
int res;
int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    res = x;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &a[i].fs, &a[i].sc);
        if(a[i].fs <= x) {
            b+=a[i].sc;
            i--;
            n--;
        }
    }
    res -= b;
    qsort(a, n, sizeof(pair), cmpP);
    for(int i = 0; i < n; i++) {
        b += a[i].sc;
        res = min(res, a[i].fs-b);
    }
    printf("%d\n", res);
    return 0;
}
