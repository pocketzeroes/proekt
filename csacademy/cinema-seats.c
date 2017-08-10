#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


char*s;
char buff[200000];
int main()
{
    int cases, caseno=0, n, i, j, k, cnt, sum;
    scanf("%s", &buff);
    s = buff;
    n = strlen(buff);
    j = 0;
    sum = 0;
    cnt = 0;
    int zero = 0;
    for(i=0;i<=n-1;i++)
    {
        if(s[i] == '1')
            cnt++;
        else
            zero++;
        while(cnt > 1 && j < i)
        {
            if(s[j] == '1') 
                cnt--;
            j++;
        }
        sum = max(sum, i-j+1);
    }
    printf("%d\n", min(sum, zero) );
    return 0;
}
