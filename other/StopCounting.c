#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

void swap(ll*nums, ll i, ll j) {
   ll t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(ll*nums,ll start,ll end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

double highest_avg(ll N, ll*deck){
    double highest_avg = 0;
    double total       = 0;
    for(int i=0; i<N; i++){
        total += deck[i];
        if(total /(double)(i + 1) > highest_avg)
            highest_avg = total/(double)(i + 1);
    }
    return highest_avg;
}
int main(){
    ll N;
    scanf("%lld", &N);
    ll cards[N];
    for(int z=0; z<N; z++)
        scanf("%lld", &cards[z]);
    double a1 = highest_avg(N, cards);
    reverse(cards, 0, N-1);
    double a2 = highest_avg(N, cards);
    printf("%.9lf\n", fmax(a1, a2));
    return 0;
}
