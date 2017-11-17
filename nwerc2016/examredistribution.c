#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;

int cmpP(const void*pa,const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

int n, sum;
pair students[100];

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &students[i].first);
        students[i].second = i + 1;
        sum += students[i].first;
    }
    qsort(students, n, sizeof(pair), cmpP);
    if(sum - students[n-1].first < students[n-1].first)
        puts("impossible");
    else{
        for(int i = 0; i < n; i++)
            printf("%d ", students[n-1 - i].second );
        puts("");
    }
    return 0;
}
