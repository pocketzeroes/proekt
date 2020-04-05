int countLargestGroup(int n){
    int size[100]={};
    for(int i = 1; i <= n; ++i){
        int num = i;
        int val = 0;
        while(num > 0){
            val+=num%10;
            num/=10;
        }
        size[val]++;
    }
    int max = 0;
    int ans = 0;
    for(int i = 0; i < 100; ++i){
        if(size[i]>max){
            max = size[i];
            ans = 0;
        }
        if(size[i]==max)
            ans++;
    }
    return ans;
}
