#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int compP( pair a, pair b){
    if(a.first !=b.first )return(a.first <b.first )?-1:1;
    if(a.second!=b.second)return(a.second<b.second)?-1:1;
    return 0;
}
pair minP(pair a,pair b){return compP(a,b)<0?a:b;}
pair maxP(pair a,pair b){return compP(a,b)>0?a:b;}
//////////////////////

enum{ N   =(int) 1e5+10};
enum{ M   = 262150     };
enum{ inf =(int) 1e9+10};
int n,m,x,y,ans;
pair xmi[M],
     xma[M],
     ymi[M],
     yma[M];

void build(int x, int l,int r){
    if(l == r){
        scanf("%d%d",&xmi[x].first,&ymi[x].first);
        xmi[x].second = ymi[x].second  = l;
        xma[x] = xmi[x];
        yma[x] = ymi[x];
        return;
    }
    int mid = (l+r)>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
    xmi[x] = minP(xmi[x<<1], xmi[x<<1|1]);
    xma[x] = maxP(xma[x<<1], xma[x<<1|1]);
    ymi[x] = minP(ymi[x<<1], ymi[x<<1|1]);
    yma[x] = maxP(yma[x<<1], yma[x<<1|1]);
}
pair askxmi(int x,int l,int r,int c,int d){
    if(c>d)
        return newPair(inf,0);
    if(c<=l&&r<=d)return xmi[x];
    int mid=(l+r)>>1;
    pair t = newPair(inf,0);
    if(c<=mid)
        t=askxmi(x<<1,l,mid,c,d);
    if(d>mid)
        t=minP(t, askxmi(x<<1|1,mid+1,r,c,d));
    return t;
}
pair askymi(int x,int l,int r,int c,int d){
    if(c>d)
        return newPair(inf, 0);
    if(c<=l&&r<=d)
        return ymi[x];
    int mid=(l+r)>>1;
    pair t = newPair(inf, 0);
    if(c<=mid)
        t=askymi(x<<1,l,mid,c,d);
    if(d>mid)
        t = minP(t, askymi(x<<1|1,mid+1,r,c,d));
    return t;
}
pair askxma(int x,int l,int r,int c,int d){
    if(c>d)
        return newPair(-inf, 0);
    if(c<=l&&r<=d)
        return xma[x];
    int mid=(l+r)>>1;
    pair t = newPair(-inf, 0);
    if(c<=mid)
        t=askxma(x<<1,l,mid,c,d);
    if(d>mid)
        t = maxP(t, askxma(x<<1|1,mid+1,r,c,d));
    return t;
}
pair askyma(int x,int l,int r,int c,int d){
    if(c>d)
        return newPair(-inf, 0);
    if(c<=l&&r<=d)
        return yma[x];
    int mid=(l+r)>>1;
    pair t = newPair(-inf, 0);
    if(c<=mid)
        t=askyma(x<<1,l,mid,c,d);
    if(d>mid)
        t = maxP(t, askyma(x<<1|1,mid+1,r,c,d));
    return t;
}
inline int cal(int x,int y,int z){
    return max(max(askxma(1,1,n,x,z-1).first,askxma(1,1,n,z+1,y).first)-min(askxmi(1,1,n,x,z-1).first,askxmi(1,1,n,z+1,y).first),
               max(askyma(1,1,n,x,z-1).first,askyma(1,1,n,z+1,y).first)-min(askymi(1,1,n,x,z-1).first,askymi(1,1,n,z+1,y).first)
           );
}
int main(){
    scanf("%d%d",&n,&m);
    build(1,1,n);
    while(m--){
        scanf("%d%d",&x,&y);
        ans=cal(x,y,askxmi(1,1,n,x,y).second);
        ans=min(ans,cal(x,y,askxma(1,1,n,x,y).second));
        ans=min(ans,cal(x,y,askymi(1,1,n,x,y).second));
        ans=min(ans,cal(x,y,askyma(1,1,n,x,y).second));
        printf("%d\n",ans);
    }
    return 0;
}
