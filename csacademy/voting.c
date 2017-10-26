#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll judges[110000];
int n;

int cmp(const void*pb, const void*pa){
    ll*a=(ll*)pa;
    ll*b=(ll*)pb;
    return *a < *b ? -1:1;
}
int maximum(int beg) {
    ll score = 0;
    int amount = 0;
    for(int i = 0; i<(beg); i++) {
        if (amount != 0) {
            if (judges[i] * amount > n*score)
                score++;
        }
        amount++;
    }
    for (int i = n - 1; i >= beg; i--) {
        if (amount != 0) {
            if (judges[i] * amount > n*score)
                score++;
        }
        amount++;

    }
    return score;
}
int main(){
    int x;
    scanf("%d %d", &n, &x);
    for(int i = 0; i<(n); i++)
        scanf("%lld", &judges[i]);
    qsort(judges, n, sizeof(ll), cmp);// reverse
    int totMax = maximum(0);
    ll score = 0;
    int amount = 0;
    for(int i = 0; i<(n); i++) {
        if (amount != 0) {
            if (judges[i] * amount > n*score)
                score++;
        }
        amount++;
    }
    int totMin = score;
    if (totMin >= x) {
        for(int i = 0; i<(n); i++)
            printf("%d ", judges[i]);
        return 0;
    }
    if (totMax <= x) {
        for (int i = n - 1; i >= 0;i--)
            printf("%d ", judges[i]);
        return 0;
    }
    int low = 0;
    int high = n;
    while (low < high) {
        int mid = (low + high) / 2;
        if (maximum(mid) > x)
            low = mid + 1;
        else
            high = mid;
    }
    for(int i = 0; i<(low); i++)
        printf("%d ", judges[i]);
    for (int i = n - 1; i >= low; i--)
        printf("%d ", judges[i]);
    return 0;
}


















































