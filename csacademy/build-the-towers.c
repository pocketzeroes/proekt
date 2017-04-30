#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
  

enum{ MaxN =(int) 1e5 + 15};
int a[MaxN];
int b[MaxN];
int n;
int*ans=NULL;int ansSz=0;


void fail()
{
    puts("-1");
    exit(0);
}
void make3(int pos)
{
    if(pos > 1 && pos + 2 <= n && b[pos - 1] == 0)
    {
        b[pos] = 3;
        ans=pushback(ans,&ansSz,pos - 1);
        ans=pushback(ans,&ansSz,pos + 2);
        ans=pushback(ans,&ansSz,pos + 1);
        ans=pushback(ans,&ansSz,pos);
    }
    else if(pos - 2 > 0 && pos < n && b[pos - 1] == 0 && b[pos - 2] == 0)
    {
        b[pos] = 3;
        ans=pushback(ans,&ansSz, pos + 1);
        ans=pushback(ans,&ansSz, pos - 2);
        ans=pushback(ans,&ansSz, pos - 1);
        ans=pushback(ans,&ansSz, pos);
    }
    else
        fail();
}
void make2(int pos)
{
    if(pos - 1 > 0 && b[pos - 1] == 0)
    {
        b[pos] = 2;
        ans=pushback(ans,&ansSz, pos - 1);
        ans=pushback(ans,&ansSz, pos);
    }
    else if(pos + 1 <= n && b[pos + 1] == 0 && b[pos - 1] != 2)
    {
        b[pos] = 2;
        ans=pushback(ans,&ansSz, pos + 1);
        ans=pushback(ans,&ansSz, pos);
    }
    else
        fail();
}
void make1(int pos)
{
    if(b[pos - 1] == 1)
        fail();
    b[pos] = 1;
    ans=pushback(ans,&ansSz,pos);
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        if(a[i] == 3)
            make3(i);
    }
    for(int i = 1; i <= n; ++i)
        if(a[i] == 2)
            make2(i);
    for(int i = 1; i <= n; ++i)
        if(a[i] == 1)
            make1(i);
    printf("%d\n", ansSz);
    for(int i = 0; i < ansSz; ++i)
        printf("%d ", ans[i]);
    puts("");
    return 0;
}














