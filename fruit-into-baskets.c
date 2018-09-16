int max(int a,int b){return a>b?a:b;}

int cnt[40005];

int totalFruit(int*tree, int treeSz){
    int n = treeSz;
    memset(cnt, 0, n * sizeof(int));
    int j     = 0;
    int types = 0;
    int ans   = 0;
    for(int i=0; i<n; i++){
        int x = tree[i];
        if (++cnt[x] == 1)
            ++types;
        while (types > 2) {
            int y = tree[j++];
            if (--cnt[y] == 0)
                --types;
        }
        ans = max(ans, i - j + 1);
    }
    return ans;
}
