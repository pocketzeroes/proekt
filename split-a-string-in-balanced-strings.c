int balancedStringSplit(char*s){
    int cnt = 0;
    int sum = 0;
    for(int z=0;s[z];z++){char it=s[z];
        if(it=='R')
            sum++;
        else
            sum--;
        if(sum==0)
            cnt++;
    }
    return cnt;
}
