#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef unsigned int u32;
inline u32 max(u32 a, u32 b){return a>b?a:b;}
u32 n,x,i,poz1,poz2,poz3,k1,k2,st,dr,mij,v[200005],w0[200005],w1[200005];

u32 cauta1(u32 a){
    st=0;
    dr=k1;
    while(st+1<dr){
        mij=(st+dr)/2;
        if(w0[mij]<a)
            st=mij;
        else
            dr=mij;
    }
    if(w0[dr]<a)
        return dr;
    return st;
}
u32 cauta2(u32 a){
    st=0;
    dr=k2;
    while(st+1<dr){
        mij=(st+dr)/2;
        if(w1[mij]<a)
            st=mij;
        else
            dr=mij;
    }
    if(w1[dr]<a)
        return dr;
    return st;
}
int main(){
    scanf("%u %u", &n, &x);
    for(i=1; i<=n; i++){
        scanf("%u", &v[i]);
        poz1=cauta1(v[i]+x);
        if( w1[poz1+1]>=v[i]+x||poz1==k2)
            w1[poz1+1] =v[i]+x;
        if(poz1>=k2)
            k2++;
        poz2=cauta1(v[i]);
        w0[poz2+1]=v[i];
        if(poz2>=k1)
            k1++;
        poz3=cauta2(v[i]+x);
        w1[poz3+1]=v[i]+x;
        if(poz3>=k2)
            k2++;
        poz1++;
        poz2++;
        poz3++;
        if( w1[poz1]>w0[poz1]&&w0[poz1])
            w1[poz1]=w0[poz1];
        if( w1[poz2]>w0[poz2]&&w0[poz2])
            w1[poz2]=w0[poz2];
        if( w1[poz3]>w0[poz3]&&w0[poz3])
            w1[poz3]=w0[poz3];
    }
    printf("%u\n", max(k1, k2) );
    return 0;
}
