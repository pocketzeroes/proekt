inline int max(int a,int b){return a>b?a:b;}
int cmp (const void * a, const void * b){  return ( *(int*)a - *(int*)b );}

int findLHS(int*nums, int numsSz){
    qsort(nums,numsSz,sizeof(int),cmp);
    int p = 0;
    int mx = 0;
    for(int i = 0;i < numsSz;i++){
        while(p <= i && nums[i] - nums[p] > 1){
            p++;
        }
        if(nums[i] - nums[p] == 1){
            mx = max(mx, i-p+1);
        }
    }
    return mx;
}
