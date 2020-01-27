int removePalindromeSub(char*s){
    if(s==NULL || s[0]=='\0')
        return 0;
    else{
        bool is_pal = true;
        int l = 0;
        int r = strlen(s);
        --r;
        while(l < r){
            is_pal &= s[l] == s[r];
            ++l;
            --r;
        }
        return is_pal ? 1 : 2;
    }
}
