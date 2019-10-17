#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

enum{ BASE =  10000};
enum{ MAX  = 100010};

typedef struct BigInt{
    int num[MAX],
        len;
}BigInt;

BigInt newBigInt(int _){
    BigInt rez;
    rez.len=1;
    clr(rez.num);
    rez.num[1] = _;
    return rez;
}

BigInt opMul(BigInt*t, int a){
    BigInt re;
    re.len = t->len;
    int temp = 0;
    for(int i=1; i<=t->len; ++i){
        re.num[i] = temp + t->num[i] * a;
        temp = re.num[i] / BASE;
        re.num[i] %= BASE;
    }
    while(temp)
        re.num[++re.len] = temp % BASE, temp /= BASE;
    return re;
}
BigInt opDiv(BigInt*t, int a){
    BigInt re;
    re.len = t->len;
    int temp = 0;
    for(int i = t->len; i; --i){
        re.num[i] = (temp + t->num[i]) / a;
        temp = (temp + t->num[i]) % a * BASE;
    }
    while(!re.num[re.len])
        --re.len;
    return re;
}

int main(){
    int x;
    scanf("%d", &x);
    x++;
    BigInt ans = newBigInt(1);
    for(int i=2; i<=x; ++i){
        BigInt bi = opMul(&ans, (4*i-2));
        ans = opDiv(&bi, i+1);
    }
    printf("%d", ans.num[ans.len]);
    for(int i=ans.len-1; i; --i)
        printf("%04d", ans.num[i]);
    return 0;
}
