void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int freq[20];
int minimumIncompatibility(int*nums, int numsSz, int k){
    int n = numsSz;
    int valid[1<<n]; fill(valid, 1<<n, -1);
    for(int mask = 0; mask < (1 << n); ++mask){
        if(__builtin_popcount(mask) == n / k){
            for(int j = 0; j < n; ++j){
                if(mask & (1 << j))
                    ++freq[nums[j]];
            }
            bool flag = true;
            for(int j = 1; j <= n; ++j){
                if(freq[j] > 1){
                    flag = false;
                    break;
                }
            }
            if(flag){
                int lb = INT_MAX, rb = INT_MIN;
                for(int j = 1; j <= n; ++j){
                    if (freq[j] > 0) {
                        lb = fmin(lb, j);
                        rb = fmax(rb, j);
                    }
                }
                valid[mask] = rb - lb;
            }
            for(int j = 0; j < n; ++j){
                if(mask & (1 << j))
                    --freq[nums[j]];
            }
        }
    }
    int f[1<<n]; fill(f, 1<<n, -1);
    f[0] = 0;
    for(int mask = 1; mask < (1 << n); ++mask){
        if(__builtin_popcount(mask) % (n / k) == 0){
            for(int sub = mask; sub; sub = (sub - 1) & mask){
                if(valid[sub] != -1 && f[mask ^ sub] != -1){
                    if(f[mask] == -1)
                        f[mask] = f[mask ^ sub] + valid[sub];
                    else
                        f[mask] = fmin(f[mask], f[mask ^ sub] + valid[sub]);
                }
            }
        }
    }
    return f[(1<<n)-1];
}
