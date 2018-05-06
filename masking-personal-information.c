char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char ans[100000];
int  len;
char*maskPII(char*S){
    len=0;
    char*S1 = strdup("");
    int n=strlen(S),i,j;
    for(i=0; i<n; i++)
        if(S[i]=='@')
            break;
    if(i<n){
        for(j=0;j<n;j++)
            if(S[j]>='A'&&S[j]<='Z')
                S[j]+='a'-'A';
        ans[len++] = S[0];
        for(j=0;j<5;j++)
            ans[len++] = '*';
        for(i--;i<n;i++)
            ans[len++] = S[i];
    }
    else{
        for(i=0;i<n;i++)
            if(S[i]>='0'&&S[i]<='9')
                S1 = concatc(S1, S[i]);
        n = strlen(S1);
        i=0;
        if(n!=10){
            ans[len++] = '+';
            for(;i<n-10;i++)
                ans[len++] = '*';
            ans[len++] = '-';
        }
        for(;i<n-7;i++)
            ans[len++] = '*';
        ans[len++] = '-';
        for(;i<n-4;i++)
            ans[len++] = '*';
        ans[len++] = '-';
        for(;i<n;i++)
            ans[len++] = S1[i];
    }
    ans[len]='\0';
    return strdup(ans);
}
