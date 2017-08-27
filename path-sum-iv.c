bool is_ancestor(int x, int y){
    int Dx=x/100, 
        Dy=y/100;
    int Px=x%100/10, 
        Py=y%100/10;
    if(Dx>Dy) 
        return false;
    while(Dy>Dx) {
        --Dy; 
        Py=(Py+1)/2; 
    }
    if(Px!=Py) 
        return false;
    return true;
}
int pathSum(int*nums, int numsSz){
    int cnt     [32]={};
    int non_leaf[32]={};
    int n = numsSz;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(i!=j && is_ancestor(nums[i], nums[j])) 
                non_leaf[i]=1;
        }
    }
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(!non_leaf[j] && is_ancestor(nums[i], nums[j])) 
                cnt[i]++;
        }
    }
    int ret=0;
    for(int i=0;i<n;i++) 
        ret += cnt[i] * (nums[i]%10);
    return ret;
}
