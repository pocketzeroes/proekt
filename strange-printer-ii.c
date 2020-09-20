int inf = 111;

bool isPrintable(int**a, int aSz, int*a0sz){
    int n = aSz, m = a0sz[0];
    int vst[111]={0};
    for(;;){
        bool ok = 0;
        for(int c = 1; c <= 60; c++){
            if(vst[c]) 
                continue;
            int mxx = -1, mnx = inf, mxy = -1, mny = inf;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    if(a[i][j] == c) {
                        mxx = fmax(mxx, i);
                        mnx = fmin(mnx, i);
                        mxy = fmax(mxy, j);
                        mny = fmin(mny, j);
                    }
                }
            }
            if(mxx == -1)
                continue;
            bool flag = true;
            for(int i = mnx; i <= mxx; i++) {
                for(int j = mny; j <= mxy; j++) {
                    if(a[i][j] != c && a[i][j] != -1) {
                        flag = false;
                        break;
                    }
                }
            }
            if(flag) {
                for(int i = mnx; i <= mxx; i++) {
                  for(int j = mny; j <= mxy; j++) {
                    a[i][j] = -1;
                  }
                }
                vst[c] = 1;
                ok = 1;
                break;
            }
        }
        if(!ok)
            break;
    }
    int cnt = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
          if(a[i][j] == -1) 
              cnt++;
        }
    return cnt == n * m;
}
