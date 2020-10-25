char slowestKey(int*releaseTimes, int releaseTimesSz, char*keysPressed){
    int Max=0,last=0;
    char res;
    for(int i =0;i<releaseTimesSz;i++){
        int ti=releaseTimes[i]-last;
        last=releaseTimes[i];
        if(ti>Max){
            Max=ti;
            res=keysPressed[i];
        }
        if(ti==Max){
            res = fmax(res, keysPressed[i]);
        }
    }
    return res;
}
