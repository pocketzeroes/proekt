#define _GNU_SOURCE 1
#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
char*substr(const char* str, size_t begin, size_t len){
  return strndup(str + begin, len); 
}

void solve(){
    char*s;
    char*s1="KICK";
    char*s2="START";
    s=getstr();
    int s_size =strlen(s);
    int s1_size=4;
    int s2_size=5;
    ll a1=0, a2=0;
    for(int i=0; i<s_size; i++){
        if(i+1>=s1_size &&strncmp(s+i+1-s1_size, s1, s1_size)==0)
            ++a2;
        if(i+1>=s2_size &&strncmp(s+i+1-s2_size, s2, s2_size)==0)
            a1+=a2;
    }
    printf("%lld\n", a1);
}
int main(){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; i++){
        printf("Case #%d: ", i+1);
        solve();
    }
    return 0;
}
