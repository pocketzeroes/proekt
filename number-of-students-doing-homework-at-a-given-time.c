int busyStudent(int*startTime, int startTimeSz, int*endTime, int endTimeSz, int queryTime){
    int ans=0;
    for(int i=0; i<startTimeSz; ++i){
        if(startTime[i] <= queryTime && queryTime <= endTime[i])
            ans++;
    }
    return ans;
}
