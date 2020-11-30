#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int*mostCompetitive(int*nums, int numsSz, int k, int*rsz){
    int n = numsSz;
    int next[n]; clr(next);
    for(int i = n - 1; i >= 0; i--){
        int go = i + 1;
        while(go < n && nums[go] >= nums[i]){
            go = next[go];
        }
        next[i] = go;
    }
    int*ans = calloc(k, sizeof(int));
    int wpos = 0;
    for(int i = 0; i < n && wpos < k; i++){
        if(next[i] + (k - wpos) <= n){
            i = next[i] - 1;
            continue;
        }
        ans[wpos++] = nums[i];
    }
   *rsz=k;
    return ans;
}
