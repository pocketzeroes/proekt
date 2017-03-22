char findTheDifference(char*s,char*t){
    char r=0;
    for(int i=0;s[i];i++){char c=s[i]; r^=c;}
    for(int i=0;t[i];i++){char c=t[i]; r^=c;}
    return r;
}
