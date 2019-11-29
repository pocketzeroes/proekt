#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

char buff[1000000];
char*getstr(){
  int rv = scanf("%s", &buff);
  if(rv!=1)return NULL;
  return strdup(buff);
}
typedef long long ll;

int main(){
    char*pattern;
    for(ll cs = 1; (pattern=getstr())!=NULL; ++cs){
        ll sum = 0;
        for(ll i=0; pattern[i]; ++i)
            sum += pattern[i] - '0';
        int pattern_sz=strlen(pattern);
        if(sum % pattern_sz != 0)
            printf("%s: invalid # of balls\n", pattern);
        else{
            bool taken[pattern_sz]; clr(taken);
            bool success = true;
            for(ll i=0; i < pattern_sz; ++i){
                ll spot = (i + pattern[i] - '0') % pattern_sz;
                if(taken[spot]){
                    success = false;
                    break;
                }
                taken[spot] = true;
            }
            if(success)
                printf("%s: valid with %lld balls\n", pattern, sum/pattern_sz);
            else
                printf("%s: invalid pattern\n", pattern);
        }
    }
    return 0;
}
