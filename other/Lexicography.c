#pragma GCC optimize "-O3"// https://open.kattis.com/problems/lexicography
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef long long ll;
enum{MAX_LEN = 16};
typedef struct{
    int a[256];
}mci;

ll factorial(int k){
    ll ans=1;
    for(int j=2; j<=k; j++)
        ans *= j;
    return ans;
}
ll count(int length, mci*freq){
    ll answer = factorial(length);
    for(int z=0;z<256;z++){int it = freq->a[z];
        if(it>1)
            answer /= factorial(it);
    }
    return answer;
}
mci profile(char*s){
    mci counts={};
    for(int j=0; s[j]; j++)
        counts.a[s[j]]++;
    return counts;
}
char*solve(char*original, ll rank){
    char*answer=strdup("");
    mci freq = profile(original);
    for(int length=strlen(original); length>0; --length){
        for(int z=0;z<256;z++){int it = freq.a[z];
            if(it>0){
                freq.a[z]--;
                ll sub = count(length-1, &freq);
                if(sub>=rank){
                    answer = concatc(answer, z);
                    break;  
                }
                else{
                    freq.a[z]++;
                    rank-=sub;
                }
            }
        }
    }
    return answer;
}
int main(){
    while(1){
        char*orig = getstr();
        ll K;
        scanf("%lld", &K);
        if(K == 0)
            break;
        puts(solve(orig, K));
    }
    return 0;
}
