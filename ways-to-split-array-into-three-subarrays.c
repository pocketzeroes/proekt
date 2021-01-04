int waysToSplit(int*a, int aSz){
    int sum[100010];
    int i, j, k, start, stop, mid, n = aSz, right, left, R;
    int res = 0, mo = 1000000007;
    sum[0] = 0;
    for(i = 1; i <= n; ++i)
      sum[i] = sum[i - 1] + a[i - 1];
    for(i = 3; i <= n; ++i){
        R = sum[n] - sum[i - 1];
        if(sum[i - 1] > R + R)
          break;
        start = 1;
        stop = i - 2;
        right = -1;
        while(start <= stop){
            mid = (start + stop) / 2;
            if(sum[mid] <= sum[i - 1] - sum[mid]){
                right = mid;
                start = mid + 1;
            }
            else
              stop = mid - 1;
        }
        if(right == -1)
          continue;
        start = 1;
        stop = right;
        left = -1;
        while(start <= stop){
            mid = (start + stop) / 2;
            if(sum[i - 1] - sum[mid] <= R){
                left = mid;
                stop = mid - 1;
            }
            else
              start = mid + 1;
        }
        if(left == -1)
          continue;
        res += right - left + 1;
        if(res >= mo)
          res -= mo;
    }
    return res;
}
