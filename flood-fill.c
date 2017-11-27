int t;
int aSz;
int a0sz;

void dfs(int**a, int r, int c, int nc){
    if(r < 0 || c < 0 || r >= aSz || c >= a0sz || a[r][c] != t)
        return;
    a[r][c] = nc;
    dfs(a, r - 1, c, nc);
    dfs(a, r + 1, c, nc);
    dfs(a, r, c - 1, nc);
    dfs(a, r, c + 1, nc);
}
int**floodFill(int**img, int imgSz, int img0sz, int sr, int sc, int newColor, int**colSzs, int*rsz){
    if(img[sr][sc] == newColor){
        int*cols = calloc(imgSz, sizeof(int));
        for(int i=0;i<imgSz;i++)
            cols[i]=img0sz;
       *colSzs = cols;
       *rsz=   imgSz;
        return img;
    }
    t = img[sr][sc];
    aSz  = imgSz;
    a0sz = img0sz;
    dfs(img, sr, sc, newColor);
    
    int*cols = calloc(imgSz, sizeof(int));
    for(int i=0;i<imgSz;i++)
        cols[i]=img0sz;
   *colSzs = cols;
   *rsz=   imgSz;
    return img;
}
