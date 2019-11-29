#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int cmp(const void * a, const void * b){
   return ( *(char*)a - *(char*)b );
}

bool is_sorted(char*a){
  for(int i=1; a[i]; i++)
    if(a[i-1] > a[i])
      return 0;
  return 1;
}
int solution(char*s){
    int answer=0;
    while(!is_sorted(s)){
        char*vv[4]={"PCC", "PPC", "PCP", "CPC"};
        for(int z=0;z<4;z++){char*p = vv[z];
            char*fnd = strstr(s, p);
            if(fnd != NULL){
                int i = fnd - s;
                qsort(s+i, 3, sizeof(char), cmp);
                goto nxt;
            }
        }
      nxt:;
        answer++;
    }
    return answer;
}
int main(){
    char*s = getstr();
    printf("%d\n", solution(s));
    return 0;
}
