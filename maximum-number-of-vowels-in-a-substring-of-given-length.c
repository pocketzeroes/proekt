#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int f[100010];
int maxVowels(char*s, int k){
    clr(f);
    int n = strlen(s);
    int i, j;
    f[0] = 0;
    for(i=1; i<=n; ++i){
        if(s[i-1]=='a'||s[i-1]=='e'||s[i-1]=='i'||s[i-1]=='o'||s[i-1]=='u')
            f[i] = f[i -1]+1;
        else
            f[i] =f[i-1];
    }
    int res = 0;        
    for(i=k; i<=n; ++i)
        if(f[i]-f[i-k]>res)
            res = f[i] - f[i-k];
    return res;
}
