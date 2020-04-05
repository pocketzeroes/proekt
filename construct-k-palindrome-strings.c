bool canConstruct(char*s, int k){
    int minst = 0;
    int maxst = 0;
    int cs[26]={};
    for(int z=0;s[z];z++){char c = s[z];
        cs[c-'a']++;
    }
    for(int i = 0; i < 26; ++i){
        minst += cs[i]%2;
        maxst += cs[i];
    }
    return minst<=k&&k<=maxst;
}
