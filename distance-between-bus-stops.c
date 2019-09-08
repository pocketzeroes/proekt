
int distanceBetweenBusStops(int*distance, int distanceSz, int start, int destination){
    int S,T,sum=0;
    int i;
    for(i=0;i<distanceSz;i++){
        if(i==start) S=sum;
        if(i==destination) T=sum;
        sum+=distance[i];
    }
    return fmin(abs(T-S), sum-abs(T-S));
}
