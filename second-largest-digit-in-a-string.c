int secondHighest(char*s){
    int f[10]={0};
    for(int z=0;s[z];z++){char c = s[z];
        if(c >= '0' && c <= '9')
            f[c-'0']++;
    }
    int num = 0;
    for(int i=9; i>=0; i--){
        if(f[i]>0){
            if(++num == 2)
                return i;
        }
    }
    return-1;
}
