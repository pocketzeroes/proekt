#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
    int a[50];
}arr;
typedef long long ll;
int T;
int N;

int fwin2(arr v){
    ll cc=0;
    for(int i=0; i<N; i++)
        if(v.a[i])
            cc += (1LL << (v.a[i] - 1));
    int nm = __builtin_popcountll(cc);
    for(int i=0; i<N-1; i++)
        if(v.a[i] > 0 && v.a[i+1] > 0 && abs (v.a[i] - v.a[i+1]) == 1)
            return 1;
    if(nm == N)
        return 0;
    if(nm % 2 == 1){
        for(int i=0; i<N; i++)
            if(!v.a[i])
                for(int j=0; j<N; j++)
                    if(!(cc&1LL<<j)){
                        v.a[i] = j+1;
                        if(!fwin2(v))
                            return 0;
                        v.a[i] = 0;
                    }
        return 1;
    }
    for(int i=0; i<N; i++){
        if(v.a[i] > 0){
            if((i > 0 && v.a[i-1] == 0) || (i < N - 1 && v.a[i+1] == 0))
                if((v.a[i] > 1 && ((cc & (1LL << (v.a[i] - 2))) == 0)) ||
                   (v.a[i] < N && ((cc & (1LL << (v.a[i]))) == 0)))
                    return 1;
        }
    }
    int sp = 0;
    int scur = 0, smax = 0;
    for(int i=0; i<N; i++){
        if(!v.a[i]){
            scur++;
            smax = fmax(smax, scur);
        }
        else{
            sp += scur % 2;
            scur = 0;
        }
    }
    sp += scur % 2;
    int lcur = 0, lmax = 0;
    for(int i=0; i<N; i++){
        if(cc & (1LL << i)){
            sp += lcur % 2;
            lcur = 0;
        }
        else{
            lcur++;
            lmax = fmax(lmax, lcur);
        }
    }
    sp += lcur % 2;
    if(lmax >= 3 && smax >= 3)
        return 1;
    if((N - nm) % 2 == 1)
        if(sp <= N - nm)
            return 1;
    if(nm == N - 2){
        if(lmax == 2 && smax == 2)
            return 1;
    }
    return 0;
}
void gogo(){
    scanf("%d", &N);
    arr v;
    int s[N+1];
    for(int i=0; i<N; i++)
        v.a[i] = 0;
    s[0] = fwin2(v);
    for(int i=0; i<N; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        v.a[a-1] = b;
        s[i+1] = fwin2(v);
    }
    int r1=0, r2=0;
    for(int i=0; i<N; i += 2)
        if(s[i] == 1 && s[i+1] == 0)
            r1++;
    for(int i=1; i<N; i+=2)
        if(s[i] == 0 && s[i+1] == 1)
            r2++;
    printf("%d %d\n", r1, r2);
}
int main(){
    scanf("%d", &T);
    for(int i=1; i<=T; i++){
        printf("Case #%d: ", i);
        gogo();
    }
    return 0;
}
