#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

char*v[112];
bool b[112];
char buff[100000];

char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
int main(){
    ll n;
    scanf("%lld", &n);
    for(ll i=0; i<n; i++){
        scanf("%s", &buff);
        v[i] = strdup(buff);
    }
    for(ll i=0; i<n; i++){
        for(ll j=0; j<n; j++){
            if(i != j){
                char*s = concats(v[i], v[j]);
                for(ll k=0; k<n; k++){
                    if(strcmp(v[k], s) == 0)
                        b[k] = 1;
                }
                free(s);
            }
        }
    }
    for(ll i=0; i<n; i++)
        if(b[i])
            printf("%d ", i+1);
    puts("");
    return 0;
}
