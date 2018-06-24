char*s;
long long dfs(char*s, int l, int r){
    if(r-l == 2)
        return 1;
    if(r-l <= 0)
        return 0;
    int h = 0;
    for(int i = l;i < r;i++){
        if(s[i] == '(')
            h++;
        else
            h--;
        if(h == 0){
            if(i-l+1 == 2)
                return 1 + dfs(s, i+1, r);
            return
            dfs(s, l+1, i) * 2 + dfs(s, i+1, r);
        }
    }
    assert(!"throw new RuntimeException");
}
int scoreOfParentheses(char*S){
    s = S;
    return (int)dfs(s, 0, strlen(S));
}
