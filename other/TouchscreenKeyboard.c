#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int  first;
  char*second;
}pair;
pair newPair(int a, char*b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  int rv;
  rv = strcmp(a->second, b->second);
  if(rv!=0)return(rv < 0)?-1:1;
  return 0;
}
//////////////////////////////////
char*keyboard[3] = {"qwertyuiop","asdfghjkl","zxcvbnm"};
char*res;
char*cur;
int x[256],y[256], tc, N;

int main(){
    for (int i = (0); i < (3); i++){
        for (int j = (0); j <strlen(keyboard[i]); j++){
            x[keyboard[i][j]] = i;
            y[keyboard[i][j]] = j;
        }
    }
    scanf("%d", &tc);
    while(tc--){
        res=getstr();
        scanf("%d", &N);
        pair liste[N];
        int gn=N;
        while(N--){
            cur = getstr();
            int dif = 0;
            for (int i = (0); res[i]; i++)
                dif += abs(x[res[i]]-x[cur[i]]) +
                       abs(y[res[i]]-y[cur[i]]);
            liste[N] = newPair(dif, cur);
        }
        qsort(liste, gn, sizeof(pair), cmpP);
        for (int i = (0); i < gn; i++)
            printf("%s %d\n", liste[i].second, liste[i].first);
    }
    return 0;
}
