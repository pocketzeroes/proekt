int min(int a,int b){return a<b?a:b;}

int countBinarySubstrings(char*s){
    int now = s[0];
    int n = strlen(s);
    int last = 0;
    int res = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (now != s[i]) {
            res += min(cnt, last);
            last = cnt;
            cnt = 1;
            now = s[i];
        } 
        else {
            cnt++;
        }
    }
    res += min(cnt, last);
    return res;
}
