#define max(a,b) (((a)>(b))?(a):(b))
int binaryGap(int N){
    int prev = -1;
    int ret  = 0;
    for(int i = 0;i < 31;i++){
        if(N<<~i<0){
            if(prev >= 0){
                ret = max(ret, i - prev);
            }
            prev = i;
        }
    }
    return ret;
}
