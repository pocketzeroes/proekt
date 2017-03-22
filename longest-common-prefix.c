
char*longestCommonPrefix(char** strs,int len) {
    if(len==0) return "";
    char*lcp=malloc(4096);
    int lcpLen=0;
    for(int i=0;i<strlen(strs[0]);i++){
        char c=strs[0][i];
        for(int j=0;j<len;j++){
            char*s=strs[j];
            if(strlen(s)<i+1||c!=s[i])
                goto end;
        }
        lcp[lcpLen++]=c;
    }
end:
    lcp[lcpLen]='\0';
    return lcp;
}
