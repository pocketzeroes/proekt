int leastInterval(char* tasks, int tasksSz, int n){
    int t = 0;
    int cnt [128] = {};
    int prev[128] = {};
    for(int i=0;i<='Z';i++) 
        prev[i] = -n-1;
    for(int i=0;i<tasksSz;i++){char x = tasks[i];
        cnt[(int)x]++;
    }
    int all=(int)tasksSz;
    while(all>0) {
        int best=0;
        for(int i='A';i<='Z';i++) 
            if(cnt[i] > 0 && cnt[i] > cnt[best] && prev[i] + n + 1 <= t) {
                best = i;
            }
        if(best) {
            --cnt[best];
            prev[best] = t;
            --all;
        }
        ++t;
    }
    return t;
}
