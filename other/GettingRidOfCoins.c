#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int v[4] = {1, 5, 10, 25};

int main(){
    int price, avail[4];
    scanf("%d", &price);
    for(int i=0; i<4; ++i)
        scanf("%d", &avail[i]);
    int msz=price/5+1;
    int ma[msz]; fill(ma, msz, -1);
    ma[0] = 0;
    for(int j=1; j<4; ++j){
        int cnt[msz]; memset(cnt, 0, sizeof(cnt));
        int upper = msz - v[j]/5;
        for(int i=0; i<upper; ++i)
          if (ma[i] >= 0 && cnt[i] < avail[j])
            if (ma[i + v[j] / 5] == -1){
                ma [i + v[j] / 5] = ma [i] + 1;
                cnt[i + v[j] / 5] = cnt[i] + 1;
            }
    }
    int res = -1;
    for (int i = 0; i * 5 <= price; i++)
        if (ma[i] >= 0 && price - i * 5 <= avail[0])
            res = fmax(res, ma[i] + price - i * 5);
    if(res == -1)
        puts("Impossible");
    else
        printf("%d\n", res);
    return 0;
}
