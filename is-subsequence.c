bool isSubsequence(char*s,char*t) {
    int slength=strlen(s);
    if(slength==0)
        return true;
    int i = 0;
    for(int z=0;t[z];z++){
        char c=t[z];
        if (c == s[i]) 
            ++i;
        if (i == slength)
            break;
    }
    return i == slength;
}
