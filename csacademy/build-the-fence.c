#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int*H;
int Hsz;

int max_element(int*arr,int sz){
    int maxe=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]>maxe)
            maxe=arr[i];
    return maxe;
}
bool f(int h, ll qnt){
    if (!h)
        return true;
    for(int i=0;i<Hsz;i++){int x = H[i];
        qnt -= x / h;
    }
    return qnt <= 0;
}
int search(ll qnt){
    int from = 0, to = max_element(H, Hsz);
    while(from < to){
        int mid = (from + to + 1) / 2;
        if(f(mid, qnt))
            from = mid;
        else
            to = mid - 1;
    }
    return from;
}
int main(){
    int n;
    ll k;
    scanf("%d %lld", &n, &k);
    Hsz = n;
    H = calloc(n, sizeof(int));
    for(int i=0; i<n; i++){
        scanf("%d", &H[i]);
    }
    int ans = search(k);
    printf("%d\n", ans);
    return 0;
}
