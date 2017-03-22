int firstUniqChar(char*s) {
    int map[128];
    memset(map,0,sizeof(map));
    for(int i=0;s[i];i++){
        char c=s[i];
        map[c]++;
    }
    for(int i = 0; s[i]; i++)
        if(map[s[i]] == 1) 
            return i;
    return -1;
}
