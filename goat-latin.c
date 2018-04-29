char ans[100000];
int  ansSz;
char*toGoatLatin(char*S){
    ansSz=0;
    int n = strlen(S), i, j, k, l;
    for(i=0,k=1; i<n; i=j+1,k++){
        for(j=i; j<n && S[j]!=' '; j++);
        if(S[i]=='a'||S[i]=='e'||S[i]=='i'||S[i]=='o'||S[i]=='u'||S[i]=='A'||S[i]=='E'||S[i]=='I'||S[i]=='O'||S[i]=='U')
            for(l=i; l<j; l++)
                ans[ansSz++] = S[l];
        else{
            for(l=i+1;l<j;l++)
                ans[ansSz++] = S[l];
            ans[ansSz++] = S[i];
        }
        ans[ansSz++] = 'm';
        for(l=0;l<=k;l++)
            ans[ansSz++] = 'a';
        if(j!=n)
            ans[ansSz++] = ' ';
    }
    ans[ansSz]='\0';
    return strdup(ans);
}
