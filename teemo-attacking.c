int findPoisonedDuration(int*ts,int tsSz, int duration){
    int tp = 0, pe = 0;
    for(int i=0; i<tsSz; ++i){
        tp += duration - (ts[i] < pe) *(pe - ts[i]);
        pe = ts[i] + duration;
    }
    return tp;
}