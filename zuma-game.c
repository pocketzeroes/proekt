bool vis[5];
int dfs(char *oco, int *ocn, int len, int depth, char*hand) {
    if (len == 0) {
        return depth;
    } 
    else if (depth >= strlen(hand) ) {
        return -1;
    }
    int res = -1;
    char color[21]; int ccnt[21];
    for (int i=0; hand[i]; ++i) {
        if (vis[i]) { continue; }
        vis[i] = true;
        for (int j=0; j<len; ++j) {
            if (hand[i] == oco[j]) {
                int val;
                for (int k=0; k<j; ++k) {
                    color[k] = oco[k];
                    ccnt[k] = ocn[k];
                }
                if (ocn[j] >= 2) {
                    int left = j-1, right = j+1;
                    while (left>=0 && right<len && color[left] == oco[right]) {
                        ccnt[left] += ocn[right];
                        if (ccnt[left] > 2) {
                            --left;
                        }
                        ++right;
                    }
                    for (int k=right; k<len; ++k) {
                        ++left;
                        color[left] = oco[k];
                        ccnt[left] = ocn[k];
                    }
                    val = dfs(color, ccnt, left+1, depth+1, hand);
                } 
                else {
                    color[j] = oco[j];
                    ccnt[j] = ocn[j]+1;
                    for (int k=j+1; k<len; ++k) {
                        color[k] = oco[k];
                        ccnt[k] = ocn[k];
                    }
                    val = dfs(color, ccnt, len, depth+1, hand);
                }
                if (res < 0 || (val >= 0 && val < res)) { res = val; }
            }
        }
        vis[i] = false;
    }
    return res;
}
int findMinStep(char*board,char*hand){
    char color[21];
    int  ccnt [21];
    char last = board[0];
    ccnt [0] = 1; 
    color[0] = last;
    int idx = 0;
    for (int i=1; board[i]; ++i) {
        if (board[i] != last) {
            ccnt[++idx] = 0;
            color[idx] = last = board[i];
        }
        ++ccnt[idx];
    }
    for (int i=0; hand[i]; ++i) { 
      vis[i] = false;
    }
    return dfs(color, ccnt, idx+1, 0, hand);
}



















