#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
typedef struct{
    double first_first;
    double first_second;
    char*  second;
}pair;
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first_first  != b->first_first) return(a->first_first  < b->first_first )?-1:1;
  if(a->first_second != b->first_second)return(a->first_second < b->first_second)?-1:1;
  return strcmp(a->second, b->second);
}
//////////////////////////////////

int main(){
    int n;
    scanf("%d", &n);
    pair a[n];
    for(int i=0; i<n; ++i){
        a[i].second = getstr();
        scanf("%lf %lf", &a[i].first_second, &a[i].first_first);
    }
    qsort(a, n, sizeof(pair), cmpP);
    int    fst   = 0;
    double btime = 1e100;
    for(int i = 0; i < n; ++i){
        double t = a[i].first_second;
        for(int j = 0, jj = 0; j < 3; ++j, ++jj){
            if(jj == i)
                ++jj;
            t += a[jj].first_first;
        }
        if (t < btime){
            btime = t;
            fst   = i;
        }
    }
    printf("%lf\n%s\n", btime, a[fst].second);
    for(int j=0, jj=0; j<3; ++j, ++jj){
        if(jj == fst)
            ++jj;
        puts(a[jj].second);
    }
    return 0;
}
