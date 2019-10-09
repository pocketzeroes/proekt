#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define Swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)

void swap(int*nums, int i, int j){
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}
///////////////////////////////////
typedef long long ll;
ll best;

void check(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
    ll w1 = x1 + x2 + x3;
    ll h1 = fmaxl(fmaxl(y1, y2), y3);
    ll area = w1*h1;
    if(y1 >= y2){
        ll w2 = fmaxl(x1+x2, x3);
        ll h2 = y1 + y3;
        area = fminl(area, w2*h2);
    }
    best = fminl(best, area);
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        best = 5e18;
        ll a[4], b[4];
        scanf("%lld %lld %lld %lld %lld %lld", &a[1], &b[1], &a[2], &b[2], &a[3], &b[3]);
        int p[3] = {1, 2, 3};
        do{
            for(int k = 0; k < (1<<3); k++){
                ll x[4], y[4];
                for(int i = 1; i <= 3; i++){
                    x[i] = a[p[i-1]];
                    y[i] = b[p[i-1]];
                }
                if(k&1) Swap(x[1], y[1]);
                if(k&2) Swap(x[2], y[2]);
                if(k&4) Swap(x[3], y[3]);
                check(x[1], y[1], x[2], y[2], x[3], y[3]);
            }
        }while(next_permutation(p, 3));
        printf("%lld\n", best);
    }
    return 0;
}
