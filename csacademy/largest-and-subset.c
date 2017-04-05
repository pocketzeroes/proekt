#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n];
    for (int i = 0 ; i < n ; ++i) {
        scanf("%d ", &arr[i]);
    }
    int ans = 0;
    for (int x = 30 ; x >= 0 ; --x) {
        int cnt = 0;
        for(int i=0;i<n;i++){
            int val = arr[i];
            cnt += (val >> x) & 1;
        }
        if (cnt >= k) {
            ans |= 1 << x;
            int nw_arr[n];memset(nw_arr,0,sizeof(nw_arr));
            int nwarSz=0;
            for(int i=0;i<n;i++){
                int val = arr[i];
                if ((val >> x) & 1) {
                    nw_arr[nwarSz++]=val;
                }
            }
            for (int z = 0 ; z < n ; ++z)
              arr[z] = nw_arr[z];
        }
    }
    printf("%d", ans);
    return 0;
}
