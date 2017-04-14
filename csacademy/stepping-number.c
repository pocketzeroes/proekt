#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>
#include<limits.h>

#define int long long



#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int32_t *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

const int INF =(int) 1e18 * 8;
enum{ N = 25}; 
enum{ M = 10};
int dp[N][M];


void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

bool valid(int x){
    if(0 <= x && x < M)
        return true;
    return false;
}
int cntless(int k){
    int lk = k, sz = 0;
    int*ragham=NULL;int32_t raghamSz=0;
    while(k){
        ragham=pushback(ragham, &raghamSz, k % 10);
        sz++;
        k /= 10;
    }
    k = lk;
    reverse(ragham, 0, raghamSz-1);
    int ans = 0;
    for(int i = 1; i <= sz; i++)
        for(int j = 1; j < M; j++){
            if(i == sz && j == ragham[0])
                break;
            ans += dp[i][j];
        }
    for(int i = 1; i < sz; i++){
        for(int z = -1; z <= 1; z++)
            if(valid(ragham[i - 1] + z) && ragham[i - 1] + z < ragham[i])
                ans += dp[sz - i][ragham[i - 1] + z];
        if(labs(ragham[i] - ragham[i - 1]) > 1)
            break;
    }
    return ans;
}
bool solve(int k){
    int last = -1;
    while(k){
        int p = k % 10;
        if(abs(last - p) > 1 && last != -1)
            return false;
        k /= 10;
        last = p;
    }
    return true;
}
int32_t main(){
    for(int i = 0; i < M; i++)
        dp[1][i] = 1;
    for(int i = 2; i < N; i++)
        for(int j = 0; j < M; j++)
            for(int z = -1; z <= 1; z++)
                if(valid(j + z))
                    dp[i][j] += dp[i - 1][j + z];
    int n, k;
    scanf("%lld %lld", &k, &n);
    int S = cntless(n + 1);
    int l = n, r = INF;
    while(r - l > 1){
        int mid = (l / 2) + (r / 2);
        if(l % 2 == 1 && r % 2 == 1)
            mid++;
        if(cntless(mid + 1) - S >= k)
            r = mid;
        else
            l = mid;
    }
    printf("%lld\n", r);
    return 0;
}





























