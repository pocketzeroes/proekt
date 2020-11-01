#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)

bool canFormArray(int*arr, int arrSz, int**pieces, int piecesSz, int*pieces0sz){
    int idx = 0;
    while(idx < arrSz){
        int p = -1;
        REP(i, piecesSz)
          if(pieces[i][0] == arr[idx]) {
            p = i;
            break;
          }
        if (p == -1) 
            return false;
        bool ok = true;
        REP (i, pieces0sz[p]){
          if(arrSz <= idx + i) 
            return false;
          if(arr[idx+i] != pieces[p][i]) 
            return false;
        }
        idx += pieces0sz[p];
    }
    return true;
}
