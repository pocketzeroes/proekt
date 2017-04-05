#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

typedef char* string;
int n;
string s[120000];

int cmp(const void*pa,const void*pb){
  char*a=(char*)pa;
  char*b=(char*)pb;
  return a[0]-b[0];
}

int cmp2d(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    char*A=(char*)*ia;
    char*B=(char*)*ib;
    return strcmp(A,B);
} 
inline int min(int a,int b){return a<b?a:b;}
   int max(int a,int b){return a>b?a:b;}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
    {
        char buff[500];
        scanf("%499s",&buff);
        s[i]=strdup(buff);
    }
    for(int i = 0; i < n; ++i){
        int sisz=strlen(s[i]);
        qsort(s[i], sisz, sizeof(char), cmp);
    }
    qsort(s, n, sizeof(char*), cmp2d);
    int cnt = 0;
    int ans = 0;
    for(int i = 0; i < n; ++i){
        ++cnt;
        ans = max(ans, cnt);
        if(i == n - 1 || strcmp(s[i + 1] , s[i])!=0 )
            cnt = 0;
    }
    printf("%d", ans);
    return 0;
}






















