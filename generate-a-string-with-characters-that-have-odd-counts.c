char*generateTheString(int n){
    char*s=calloc(n+1, sizeof(char));
    for(int i=0; i<n; i++)
        s[i]='a';
    if(n%2==0)
        s[0]='b';
    return s;
}
