#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

bool checkPartitioning(char*s){
    int n = strlen(s);
    bool p[n][n]; clr(p);
    for(int i = n - 1; i >= 0; --i){
        p[i][i] = true;
        for(int j = i + 1; j < n; ++j){
            if(s[i] == s[j]){
                p[i][j] = (i + 1 == j || p[i + 1][j - 1]);
            }
        }
    }
    for(int i = 0; i < n; ++i){
        if(p[0][i]){
            for(int j = i + 1; j < n - 1; ++j){
                if(p[i + 1][j] && p[j + 1][n - 1]){
                    return true;
                }
            }
        }
    }
    return false;
}
