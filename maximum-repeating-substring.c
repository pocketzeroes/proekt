int maxRepeating(char*seq, char*word){
    int N = strlen(seq),
        M = strlen(word);
    int ret = 0;
    for(int i=(0),i_end_=(N - M + 1);i<i_end_;i++){
        int tmp = 0;
        int cur = i;
        while(cur + M <= N && strncmp(seq+cur, word, M)==0){
            tmp++;
            cur += M;
        }
        ret = fmax(tmp, ret);
    }
    return ret;
}
