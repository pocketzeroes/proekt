#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MOD =(int)1e9 + 7};
int N, P;
int A[351], allcnt[99];
int primes[26], primenum[99];
char S[999];
typedef struct{
    int n, p;
}pair;
pair L[99], R[99];
int LC, RC;
typedef struct{
    int    cnt1[26], 
           cnt2[26];
    double log;
}num;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
num*pushbackN(num*array, int *size, num value){
  num*output = resizeArray(array, num, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	num*ptr;
	int sz;
}vecn;
vecn newVecN(){
	vecn rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
vecn LD, RD;//of num
int LDC, RDC;
int nowcnt1[99],
    nowcnt2[99];

void dfs(int n, int sz, pair*arr, vecn*to){
    if (n > sz){
        num t = {0,};
        for (int i=1;i<=P;i++){
            t.cnt1[i] = nowcnt1[i], t.cnt2[i] = nowcnt2[i];
            t.log += log10(primes[i])*(nowcnt1[i] - nowcnt2[i]);
        }
        to->ptr = pushbackN(to->ptr, &to->sz, t);
        return;
    }
    for (int i=0;i<=arr[n].p;i++){
        nowcnt1[primenum[arr[n].n]] = i;
        nowcnt2[primenum[arr[n].n]] = arr[n].p-i;
        dfs(n+1, sz, arr, to);
        nowcnt1[primenum[arr[n].n]] = nowcnt2[primenum[arr[n].n]] = 0;
    }
}
int cmp1(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return(LD.ptr[*a].log < LD.ptr[*b].log)?-1:1;
}
int cmp2(const void*pa, const void*pb){
    int*a=(int*)pa;
    int*b=(int*)pb;
    return(RD.ptr[*a].log < RD.ptr[*b].log)?-1:1;
}
int main(){
    scanf("%s", S);
    for(int i=0;S[i];i+=2)
        A[++N] = (S[i]-'0')*10 + S[i+1]-'0';
    for(int i=1;i<=N;i++)
        allcnt[A[i]]++;
    for(int i=2;i<99;i++){
        if(allcnt[i]){
            primes[++P] = i;
            primenum[i] = P;
        }
    }
    int cnt = 1;
    for(int i=1;i<=P;i++){
        cnt *= (allcnt[primes[i]] + 1);
        if(cnt > 1e5){
            for(int j=i;j<=P;j++)
                R[++RC] =(pair){primes[j], allcnt[primes[j]]};
            break;
        }
        L[++LC] =(pair){primes[i], allcnt[primes[i]]};
    }
    if(!RC)
        R[++RC] =(pair){primes[1], 0};
    dfs(1, LC, L, &LD);
    dfs(1, RC, R, &RD);
    LDC = LD.sz,
    RDC = RD.sz;
    int larr[LDC]; memset(larr, 0, sizeof(larr));
    int rarr[RDC]; memset(rarr, 0, sizeof(rarr));
    for(int i=0;i<LDC;i++)
        larr[i] = i;
    for(int i=0;i<RDC;i++)
        rarr[i] = i;
    qsort(larr, LDC, sizeof(int), cmp1);
    qsort(rarr, RDC, sizeof(int), cmp2);
    double mn = 2e9;
    int lt, rt;
    for (int i=0,j=RDC-1;i<LDC;i++){
        while(j && LD.ptr[larr[i]].log + RD.ptr[rarr[j-1]].log >= 0)
            j--;
        double v = LD.ptr[larr[i]].log + RD.ptr[rarr[j]].log;
        if(v >= 0){
            if(mn > v)
               mn = v, lt = larr[i], rt = rarr[j];
        }
    }
    int num1 = 1, num2 = 1;
    for (int i=1;i<=P;i++){
        for(int j=LD.ptr[lt].cnt1[i] + RD.ptr[rt].cnt1[i];j--;)
            num1 = (ll)num1*primes[i]%MOD;
        for(int j=LD.ptr[lt].cnt2[i] + RD.ptr[rt].cnt2[i];j--;)
            num2 = (ll)num2*primes[i]%MOD;
    }
    printf("%d\n", (num1+num2)%MOD);
    return 0;
}
