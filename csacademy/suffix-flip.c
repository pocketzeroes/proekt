#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

char s[100000];
int main(){
    int n;
    scanf("%d", &n);
    scanf("%s", &s);
    int st = 0;
    while (st < n && s[st] == '0')
        st++;
    int cnt = 1;
    for (int i = st + 1; i < n; i++)
        if (s[i] != s[i - 1])
            cnt++;
    cnt %= 2;
    if (st == n)
        cnt = 0;
    printf("%d\n", cnt);
    return 0;
}

