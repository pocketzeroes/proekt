int minimumSwap(char*s1, char*s2){
    int s1size=strlen(s1);
    int s2size=strlen(s2);
    if(s1size != s2size)
        return -1;
    int x=0, y=0;
    for(int i=0; i<s1size; ++i)
        if(s1[i]=='x')
            x++;
        else
            y++;
    for(int i=0; i<s2size; ++i)
        if(s2[i]=='x')
            x++;
        else
            y++;
    if(x%2 || y%2)
        return -1;
    int cnt1=0,cnt2=0;
    for(int i=0; i<s1size; ++i){
        if(s1[i] != s2[i]){
            if(s1[i]=='x')
                cnt1++;
            else
                cnt2++;
        }
    }
    return(cnt1+1)/2+(cnt2+1)/2;
}
