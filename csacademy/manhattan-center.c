#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
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
typedef long long ll;
int n,k;
pair arr[100100];
int a;

int cmp(const void*pa, const void*pb){
    pair*p1 = (pair*)pa;
    pair*p2 = (pair*)pb;
    return(p1->second + abs(p1->first - a) < p2->second + abs(p2->first - a))?-1:1;
}
int main(){
    scanf("%d %d", &n, &k);
    for(int i=0 ; i<n; ++i)
        scanf("%d %d" , &arr[i].first , &arr[i].second);
    int l = 1,
        r = 1e8 +5;
    while(r-l > 50){
        int mid1 = l + (r-l)/3;
        int mid2 = r - (r-l)/3;
        ll sum1 = 0;
        a = mid1;
        qsort(arr, n, sizeof(pair), cmp);
        for(int i=0; i<k; ++i)
            sum1 += arr[i].second + abs(arr[i].first - mid1);
        a = mid2;
        qsort(arr, n, sizeof(pair), cmp);
        ll sum2 =  0;
        for(int i=0; i<k; ++i)
            sum2 += arr[i].second + abs(arr[i].first - mid2);
        if(sum1 <= sum2)
            r = mid2;
        else
            l = mid1;
    }
    ll ans = (ll)1e15;
    for(int i=l; i<=r; ++i){
        a = i;
        qsort(arr, n, sizeof(pair), cmp);
        ll sum = 0;
        for(int j=0; j<k; ++j)
            sum += arr[j].second + abs(arr[j].first - i);
        ans = min(ans , sum);
    }
    printf("%lld\n", ans);
    return 0;
}
