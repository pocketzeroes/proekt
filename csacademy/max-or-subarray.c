#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
void fill(int*arr,int sz, int val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}
int main() {
    int n; 
    scanf("%d", &n);
    int elements[n];
    int or_sum = 0;
    for (int i = 0; i < n; i += 1) {
        scanf("%d", &elements[i]);
        or_sum |= elements[i];
    }
    int last_seen[32];
    fill(last_seen, 32, -1);
    int answer = n; 
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < 30; j += 1) {
            if (elements[i] & (1 << j)) {
                last_seen[j] = i;
            }
        }
        int mn_last_seen = i;
        int current_or = 0;
        for (int j = 0; j < 30; j += 1) {
            if (last_seen[j] != -1) {
                mn_last_seen = min(mn_last_seen, last_seen[j]);
                current_or |= (1 << j);
            }
        }
        if (current_or == or_sum) {
            answer = min(answer, i - mn_last_seen + 1);
        }
    }
    printf("%d\n", answer);
    return 0;
}










