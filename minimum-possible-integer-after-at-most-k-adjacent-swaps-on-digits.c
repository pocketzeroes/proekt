#pragma GCC optimize "-O3"
#pragma GCC option("arch=native","tune=native","no-zero-upper") 
#pragma GCC target("avx")

#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)

char*minInteger(char*nums, int k){
    int numlen=strlen(nums);
    if(numlen == 1)
        return strdup(nums);
    int i = 0, j = 0;
    while(k && i < numlen-1){
        if(nums[i] == '0'){
            i++;
            j++;
            continue;
        }
        int p = j, steps = 0;
        while(nums[p] != '0' && j < numlen && steps <= k){
            if(nums[j] < nums[p])
                p = j;
            j++;
            steps++;
        }
        if(p == i){
            i++;
            j = i;
            continue;
        }
        for(; p>i; p--){
            swap(nums[p], nums[p-1]);
            k--;
        }
        i++;
        j = i;
        
    }
    return strdup(nums);
}
