char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}

enum{ MAXN = 301000};


int sa[MAXN],height[MAXN],rank[MAXN];
int wa[MAXN],wb[MAXN],wc[MAXN],wd[MAXN];

bool cmp(int *r,int a,int b,int l,int n){
    int la = r[a],lb = r[b],ra,rb;
    ra = a+l < n? r[a+l] : -1;
    rb = b+l < n? r[b+l] : -1;
    return (la == lb) && (ra == rb);
}
void makesa(char *r,int *sa,int n,int m){
    int *x = wa,*y = wb;
    for (int i = 0;i < m;++i)
        wc[i] = 0;
    for (int i = 0;i < n;++i)
        ++wc[x[i] = r[i]];
    for (int i = 1;i < m;++i)
        wc[i] += wc[i-1];
    for (int i = n-1;i >= 0;--i)
        sa[--wc[x[i]]] = i;
    for (int tot = 0,p = 1;tot+1 < n;p <<= 1,m = tot+1){
        tot = 0;
        for (int i = n-p;i < n;++i)
            y[tot++] = i;
        for (int i = 0;i < n;++i)
            if (sa[i] >= p)
                y[tot++] = sa[i] - p;
        for (int i = 0;i < n;++i)
            wd[i] = x[y[i]];
        for (int i = 0;i < m;++i)
            wc[i] = 0;
        for (int i = 0;i < n;++i)
            ++wc[wd[i]];
        for (int i = 1;i < m;++i)
            wc[i] += wc[i-1];
        for (int i = n-1;i >= 0;--i)
            sa[--wc[wd[i]]] = y[i];
        int *t = x; x = y; y = t;
        x[sa[0]] = tot = 0;
        for (int i = 1;i < n;++i)
            x[sa[i]] = cmp(y,sa[i-1],sa[i],p,n) ? tot : ++tot;
    }
}
void makeheight(char *r,int *sa,int *height,int n){
    for (int i = 0;i < n;++i)
        rank[sa[i]] = i;
    height[0] = 0;
    for (int i = 0;i < n;++i){
        if (!rank[i])
            continue;
        if (!i)
            height[rank[i]] = 0;
        else
            height[rank[i]] = height[rank[i-1]] - 1;
        if (height[rank[i]] < 0)
            height[rank[i]] = 0;
        for (;r[i+height[rank[i]]] == r[sa[rank[i]-1] + height[rank[i]]];++height[rank[i]]);
    }
}

char arr[MAXN];

char*longestDupSubstring(char*S){
    int n = strlen(S);
    strcpy(arr, S);
    makesa(arr, sa, n, 200);
    makeheight(arr, sa, height, n);
    int maxV = -1;
    int at   = -1;
    for(int i=1; i<n; i++){
        if (height[i] > maxV){
            maxV = height[i];
            at = i;
        }
    }
    if (maxV == 0)
        return strdup("");
    return substr(S, sa[at], maxV);
}
