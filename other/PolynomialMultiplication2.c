#pragma GCC optimize "-Ofast"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef double ld;
typedef struct{
    ld re, im;
}cmplx;
cmplx newCmplx0(){
    cmplx rez;
    rez.re = 0.;
    rez.im = 0.;
    return rez;
}
cmplx newCmplx1(ld a){
    cmplx rez;
    rez.re = a;
    rez.im = 0.;
    return rez;
}
cmplx newCmplx(ld a, ld b){
    cmplx rez;
    rez.re = a;
    rez.im = b;
    return rez;
}
ld real(cmplx c){
    return c.re;
}
cmplx cMul(cmplx c, cmplx a){
    return newCmplx(c.re*a.re - c.im*a.im,
                    c.re*a.im + c.im*a.re);
}
cmplx cAdd(cmplx c, cmplx a){
    return newCmplx(c.re+a.re, c.im+a.im);
}
cmplx cSub(cmplx c, cmplx a){
    return newCmplx(c.re-a.re, c.im-a.im);
}
const ld pi    = 3.141592653589793238462643383;
void swap(cmplx*nums, int i, int j){
   cmplx t  = nums[i];
   nums[i]  = nums[j];
   nums[j]  = t;
}
double _sin(double re){
  __asm__ ("fsin" : "+t" (re));
  return re;
}
double _cos(double re){
  __asm__ ("fcos" : "+t" (re));
  return re;
}
enum{ maxn = (1<<18)};
cmplx a[maxn*2],b[maxn*2],W[2][maxn*2];
int N,na,nb,rev[maxn*2];

void FFT(cmplx*a,int f){
    cmplx x,y;
    for(int i=0; i<N; i++)
        if (i<rev[i])
            swap(a, i, rev[i]);
    for (int i=1; i<N; i<<=1)
        for (int j=0,t=N/(i<<1); j<N; j+=i<<1)
            for (int k=0,l=0; k<i; k++,l+=t)
                x = cMul(W[f][l], a[j+k+i]),
                y=a[j+k],
                a[j+k]   = cAdd(y, x),
                a[j+k+i] = cSub(y, x);
    if (f)
        for (int i=0; i<N; i++)
            a[i].re/=N;
}
void work(){
    for (int i=0; i<N; i++){
        int x=i,y=0;
        for (int k=1; k<N; x>>=1,k<<=1){
            y<<=1;
            y|=x&1;
        }
        rev[i]=y;
    }
    for (int i=0; i<N; i++)
        W[0][i] = W[1][i] = newCmplx(_cos(2*pi*i/N),_sin(2*pi*i/N)),W[1][i].im=-W[0][i].im;
}
void init(){
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    scanf("%d",&na); na++;for (int i=0; i<na; i++) scanf("%lf", &a[i].re);
    scanf("%d",&nb); nb++;for (int i=0; i<nb; i++) scanf("%lf", &b[i].re);
    for (N=1; N<na||N<nb; N<<=1); N<<=1;
}
void doit(){
    work(),FFT(a,0),FFT(b,0);
    for(int i=0; i<N; i++)
        a[i] = cMul(a[i], b[i]);
    FFT(a,1);
    printf("%d\n",na+nb-2);
    for(int i=0; i<na+nb-1; i++)
        printf("%.0lf\n", a[i].re);
    printf("\n");
}
int main(){
    int t; 
    scanf("%d",&t);
    while(t--){
        init();
        doit();
    }
    return 0;
}
