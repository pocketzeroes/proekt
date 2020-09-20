char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}

char*a[20];
char*s;
int n, atop, res;

void dfs(int p){
    int i, j;
    if(p >= n){
        if(atop > res){
            res = atop;
        }
        return;
    }
    char*tmp;
    for(i=p; i<n; ++i){
        tmp = substr(s, p, i - p + 1);
        for(j = 0; j < atop; ++j){
            if(strcmp(tmp, a[j])==0)
                break;
        }
        if(j >= atop){
            a[atop] = tmp;
            ++atop;
            dfs(i + 1);
            --atop;
        }
    }
}
int maxUniqueSplit(char*ss){
    s = ss;
    n = strlen(s);
    atop = 0;
    res = 0;
    dfs(0);
    return res;
}
