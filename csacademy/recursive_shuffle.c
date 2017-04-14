#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int a[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &a[i]);
        a[i]--;
    }
    for (int i = 0; i < m - 1; i++)
    {
        int x = a[i], 
            y = a[i + 1];
        int t;
        if (x > y){
            t=x; x=y; y=t;
        }
        int r = 0;
        for (int j = 0; j < 31; j++)
        {
            if (x % 2 > y % 2)
                break;
            else if (x % 2 < y % 2)
            {
                r = 1;
                break;
            }
            x /= 2;
            y /= 2;
        }
        if (!r && a[i] < a[i + 1] || r && a[i] > a[i + 1])
            continue;
        return puts("0")*0;
    }
    puts("1");
    return 0;
}
