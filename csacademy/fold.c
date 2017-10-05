#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swapi(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

void swaparr(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swaparr(nums, start, end);
        start++;
        end  --;
    }
}


void link(int*next_prev, int a, int b){
    next_prev[a] ^= a ^ b;
    next_prev[b] ^= a ^ b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int top      [n]; memset(top      ,0,sizeof(top      ));
    int bottom   [n]; memset(bottom   ,0,sizeof(bottom   ));
    int next_prev[n]; memset(next_prev,0,sizeof(next_prev));
    int height   [n]; memset(height   ,0,sizeof(height   ));

    for (int i = 0; i < n; i++) {
        top   [i] = bottom[i] = i;
        height[i] = 1;
    }
    int l = 0;
    int r = n;
    bool reversed = false;

    for (int i = 0; i < m; i++) {
        int x;
        scanf("%d", &x);
        if ((r - l - x) <= x) {
            if (!reversed) {
                for (int i = 0; i < r - l - x; i++) {
                    link(next_prev, top[l + x - i - 1], top[l + x + i]);
                    top[l + x - i - 1] = bottom[l + x + i];
                    height[l + x - i - 1] += height[l + x + i];
                }
                r = l + x;
            } 
            else {
                for (int i = 0; i < r - l - x; i++) {
                    link(next_prev, bottom[l + (r - l - x) + i], bottom[l + (r - l - x) - 1 - i]);
                    bottom[l + (r - l - x) + i] = top[l + (r - l - x) - 1 - i];
                    height[l + (r - l - x) + i] += height[l + (r - l - x) - 1 - i];
                }
                l = r - x;
            }
        } 
        else {
            if (!reversed) {
                reversed = true;
                for (int i = 0; i < x; i++) {
                    link(next_prev, top[l + x + i], top[l + x - 1 - i]);
                    top[l + x + i] = bottom[l + x - 1 - i];
                    height[l + x + i] += height[l + x - 1 - i];
                }
                l = l + x;
            } 
            else {
                reversed = false;
                for (int i = 0; i < x; i++) {
                    link(next_prev, bottom[l + (r - l - x) - i - 1], bottom[l + (r - l - x) + i]);
                    bottom[l + (r - l - x) - i - 1] = top[l + (r - l - x) + i];
                    height[l + (r - l - x) - i - 1] += height[l + (r - l - x) + i];
                }
                r -= x;
            }
        }
    }

    if (reversed) {
        int tmp[n];
        memcpy(&tmp,    &top,    sizeof(top));
        memcpy(&top,    &bottom, sizeof(top));
        memcpy(&bottom, &tmp,    sizeof(top));

        reverse(top,    0, n-1);
        reverse(bottom, 0, n-1);
        reverse(height, 0, n-1);
        swapi(l, r);
        l = n - l;
        r = n - r;
    }
    int max = l;

    for (int i = l; i < r; i++) {
        if (height[i] > height[max])
            max = i;
    }
    int x = bottom[max];
    int pr = x;

    while (x != top[max]) {
        printf("%d ", x + 1);
        int nx = next_prev[x] ^ pr;
        pr = x;
        x = nx;
    }
    printf("%d\n", top[max] + 1);
    for (int i = l; i < r; i++)
        printf("%d ", bottom[i] + 1);
    puts("");
    for (int i = l; i < r; i++)
        printf("%d ", top[i] + 1);
    puts("");
    return 0;
}

























