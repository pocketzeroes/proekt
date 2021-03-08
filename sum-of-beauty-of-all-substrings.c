#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int cnt[26];

int beautySum(char*s){
    int ssize=strlen(s);
    int ans = 0;
    for(int i = 0; s[i]; i += 1){
        clr(cnt);
        for(int j = i; j < ssize; j += 1){
            cnt[s[j] - 'a'] += 1;
            int ma = 0, mi = ssize;
            for(int z=0;z<26;z++){int x = cnt[z];
              if(x){
                ma = fmax(ma, x);
                mi = fmin(mi, x);
              }
            }
            ans += ma - mi;
        }
    }
    return ans;
}
