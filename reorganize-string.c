char ans[100000];
int  ansSz;
char*reorganizeString(char*S){
    ansSz = 0;
    int l[26]; memset(l, 0, sizeof(l));
    int cur = 0;
    for(int i = 0; S[i]; i++)
        if (++l[S[i] - 'a'] > l[cur])
            cur = S[i] - 'a';
    ans[ansSz++] = 'a' + cur;
    l[cur]--;
    for (int i = 1; S[i]; i++){
        int temp = -1;
        for(int j = 0; j < 26; j++)
            if(l[j] > 0 && (j != ans[i - 1] - 'a') && (temp == -1 || l[temp] < l[j]))
                temp = j;
        if (temp == -1)
            return "";
        l[temp]--;
        ans[ansSz++] = 'a' + temp;
    }
    ans[ansSz] = '\0';
    return strdup(ans);
}
