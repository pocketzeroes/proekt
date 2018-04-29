int numFriendRequests(int*ages, int agesSz){
    int f[121]; memset(f, 0, sizeof(f));
    for(int z=0;z<agesSz;z++){int v = ages[z];
        f[v]++;
    }
    int ret = 0;
    for(int i = 0;i <= 120;i++){
        for(int j = 0;j <= 120;j++){
            if(j*2 <= i+14 || j > i || j > 100 && i < 100){
            }
            else{
                if(i == j){
                    ret += f[i] * (f[i]-1);
                }
                else{
                    ret += f[i]*f[j];
                }
            }
        }
    }
    return ret;
}
