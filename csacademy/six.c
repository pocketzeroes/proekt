#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ mod =1000000007};
enum{ maxl=14        };

ll N,K; 
int dp[20][(1<<6)],cnt[(1<<6)],C[20][20],dp2[14][14][(1<<6)],pp[20][20],f[20]; 
vec p, a;

int neg(int mask){
    return ((1<<K)-1)^mask;
}
int main(){
    scanf("%lld", &N);
    int i,j;
    for (i=2; 1LL*i*i<=N; i++){
        if (N%i==0){
            p.ptr = pushback(p.ptr, &p.sz, i);
            a.ptr = pushback(a.ptr, &a.sz, 0);
            K++;
            while (N%i==0) 
                a.ptr[K-1]++, N/=i;
        }
    }
    if(N>1){
        p.ptr = pushback(p.ptr, &p.sz, N);
        a.ptr = pushback(a.ptr, &a.sz, 0);
        K++;
        a.ptr[K-1] = 1;
    }
    int mask;
    cnt[0] = 1;
    for (mask=1; mask<(1<<K); mask++){
        for (i=0; i<K; i++)
            if (mask&(1<<i)){
                cnt[mask] = a.ptr[i]*cnt[mask^(1<<i)]%mod;
                break;
            }
    }
    f[0] = 1;
    for (i=1; i<=maxl; i++)
        f[i]=(1LL*i*f[i-1])%mod;
    ll res=0;
    for (mask=0; mask<(1<<K); mask++)
        dp[0][mask]=1;
    for (i=0; i<=maxl; i++){
        C[i][0]=1;
        for (j=1; j<=i; j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
    for (i=1; i<=maxl; i++){
        pp[i][0]=1;
        for (j=1; j<=maxl; j++)
            pp[i][j]=(1LL*i*pp[i][j-1])%mod;
    }
    for (i=1; i<=6; i++)
        for (mask=0; mask<(1<<K); mask++){
            dp2[i][0][mask]=1LL*cnt[mask]*pp[i+1][__builtin_popcount(mask)]%mod;
        }
    for (i=1; i<=6; i++){
        for (j=1; j<=i; j++){
            for (mask=0; mask<(1<<K); mask++){
                int c;
                for (c=mask; c!=0; c=(c-1)&mask){
                    dp2[i][j][mask]=(dp2[i][j][mask]+cnt[c]*cnt[c]%mod*dp2[i][j-1][mask^c])%mod;
                }
            }
        }
    }
    for (i=1; i<=12; i++){
        for (mask=0; mask<(1<<K); mask++){
            for (int umask=1; umask<(1<<K); umask++)
                if ((umask&mask)==0)
                    dp[i][mask]=(dp[i][mask]+1LL*cnt[umask]*dp[i-1][mask|umask])%mod;
            for (int cmask=neg(mask); cmask!=0; cmask=(cmask-1)&neg(mask)){
                for (j=1; j<i && j<=__builtin_popcount(cmask); j++){
                    int cr=1LL*C[i-1][j]*dp2[j][j][cmask]%mod*f[j]%mod;
                    dp[i][mask]=(dp[i][mask]+1LL*cr*dp[i-j-1][mask|cmask])%mod;
                }
            }
        }
        res=(res+dp[i][0])%mod;
    }
    printf("%lld\n", res);
    return 0;
}
