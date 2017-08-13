int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

bool isPossible(int*nums, int numsSz){
    int f[3] = {0, 0, 0};
    int l = 0;
    while (l < numsSz) {
        if (nums[l] == nums[0]) {
            l++;
        } else { break; }
    }
    if (l == numsSz) { return false; }
    f[0] = l;
    while (l < numsSz) {
        if (nums[l] > nums[l - 1] + 1) {
            if (f[0] + f[1] > 0) { return false; }
            f[0] = f[1] = f[2] = 0;
            int r = l;
            while (l < numsSz) {
                if (nums[r] == nums[l]) {
                    r++;
                } else { break; }
            }
            f[0] = r - l;
        }
        int r = l;
        while (r < numsSz) {
            if (nums[r] == nums[l]) {
                r++;
            } else { break; }              
        }
        int g[3] = {0, 0, 0};
        int num = r - l;
        if (f[0] + f[1] > num) {
            return false;
        }
        g[1] = f[0];
        g[2] = f[1];
        num-= f[0] + f[1];
        g[2] += min(num, f[2]);
        g[0] = num - min(num, f[2]);
        f[0] = g[0]; f[1] = g[1];f[2] = g[2];
        l = r;
    }
    return (f[0] + f[1] == 0);
}
