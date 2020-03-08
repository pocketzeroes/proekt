int  cnt[30];
char ans[100000];
int  asz;
char*sortString(char*s){
    asz=0;
    int z;
    for(z=0;s[z];z++){char c=s[z];
        ++cnt[c - 'a'];
    }
    int left = z;
    for(; left>0;){
        for(int i=0; i<26; ++i)
            if(cnt[i])
                --cnt[i], --left,
                ans[asz++]=(i + 'a');
        for(int i = 25; i >= 0; --i)
            if(cnt[i])
                --cnt[i], --left,
                ans[asz++]=(i + 'a');
    }
    ans[asz]='\0';
    return strdup(ans);
}
