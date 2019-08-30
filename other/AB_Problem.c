#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
typedef long long ll;
enum{ N   = 200005   };
enum{ INF = 0x3ffffff};
enum{ M = 50000    };
enum{ MAXN = 800040};
int a  [MAXN/4];
ll  num[MAXN];
ll  tt [MAXN];

typedef struct{
    double r,i;
}Complex;
Complex x1[MAXN];
Complex newComplex(double r, double i){
    return(Complex){r,i};
}
Complex opAdd(Complex a, Complex b){
    return newComplex(a.r+b.r, a.i+b.i);
}
Complex opSub(Complex a, Complex b){
    return newComplex(a.r-b.r, a.i-b.i);
}
Complex opMul(Complex a, Complex b){
    return newComplex(a.r*b.r-a.i*b.i, a.r*b.i+a.i*b.r);
}

void change(Complex*y, int len){
    int i,j,k;
    for(i = 1, j = len/2;i < len-1;i++){
        if(i < j)
            swap(y[i], y[j]);
        k = len/2;
        while( j >= k){
            j -= k;
            k /= 2;
        }
        if(j < k)
           j += k;
    }
}
void fft(Complex*y, int len, int on){
    change(y,len);
    for(int h = 2;h <= len;h <<= 1){
        Complex wn=newComplex(cos(-on*2*M_PI/h),sin(-on*2*M_PI/h));
        for(int j = 0;j < len;j += h){
            Complex w = newComplex(1,0);
            for(int k = j; k < j+h/2; k++){
                Complex u = y[k];
                Complex t = opMul(w, y[k+h/2]);
                y[k] = opAdd(u, t);
                y[k+h/2] = opSub(u, t);
                w = opMul(w, wn);
            }
        }
    }
    if(on == -1)
        for(int i = 0;i < len;i++)
            y[i].r /= len;
}
int main(){
    int n=0;
    int tot;
    scanf("%d",&tot);
    memset(num,0,sizeof(num));
    memset(tt,0,sizeof(tt));
    int cnt0=0;
    int aa;
    for(int i = 0;i < tot;i++){
        scanf("%d",&aa);
        if(aa==0){
            cnt0++;
            continue;
        }
        else
            a[n]=aa;
        num[a[n]+M]++;
        tt[a[n]+M]++;
        n++;
    }
    qsort(a, n, sizeof(int), cmp);
    int len1 = a[n-1]+M+1;
    int len = 1;
    while( len < 2*len1 ) 
        len <<= 1;
    for(int i = 0;i < len1;i++){
        x1[i] = newComplex(num[i],0);
    }
    for(int i = len1;i < len;i++){
        x1[i] =newComplex(0,0);
    }
    fft(x1,len,1);
    for(int i = 0;i < len;i++){
        x1[i] = opMul(x1[i], x1[i]);
    }
    fft(x1,len,-1);
    for(int i = 0;i < len;i++){
        num[i] = (ll)(x1[i].r+0.5);
    }
    len = 2*(a[n-1]+M);
    for(int i = 0;i < n;i++)
        num[a[i]+a[i]+2*M]--;
    ll ret= 0;
    int l=a[n-1]+M;
    for(int i = 0;i <=l; i++){
        if(tt[i])
            ret+=(ll)(num[i+M]*tt[i]);
    }
    ret+=(ll)(num[2*M]*cnt0);
    if(cnt0!=0){
        if(cnt0>=3){
            ll tmp=1;
            tmp*=(ll)(cnt0);
            tmp*=(ll)(cnt0-1);
            tmp*=(ll)(cnt0-2);
            ret+=tmp;
        }
        for(int i = 0;i <=l; i++){
            if(tt[i]>=2){
                ll tmp=(ll)cnt0;
                tmp*=(ll)(tt[i]);
                tmp*=(ll)(tt[i]-1);
                ret+=tmp*2;
            }
        }
    }
    printf("%lld\n",ret);
    return 0;
}
