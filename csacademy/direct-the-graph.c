#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

char*string(int num, char chr){
  char spce[num+1]; memset(spce, chr, sizeof(spce)); spce[num]='\0';
  return strdup(spce);
}

int main(){
    int n;
    scanf("%d", &n);
    long long ans = 1LL * n * (n - 1) * (n - 2) / 6;
    long long bad = 0;
    int n2 = n / 2;
    bad = 1LL * n * ((n2 * (n2 - 1) / 2) + (n - n2 - 1) * (n - n2 - 2) / 2);
    bad /= 2;
    printf("%lld\n", (ans - bad) % (int)(1e9 + 7) );
    for (int i = n - 1; i; i--){
        printf("%s%s", string(i - n2, '0') , string(n2, '1') );
        n2 -= 1;
        n2 = max(n2, 0);
    }
    return 0;
}
