typedef long long ll;
int cmp(const void*pa, const void*pb){
    ll*a=(ll*)pa;
    ll*b=(ll*)pb;
    return *a < *b ? -1:1;
}
int carFleet(int target, int*position, int positionSz, int*speed, int speedSz){
    int n = positionSz;
    ll ps[n+1];
    for(int i=0; i<n; i++)
        ps[i] = (((ll)position[i])<<32) + speed[i];
    qsort(ps, n, sizeof(ll), cmp);
    double time[n+1]; memset(time, 0, sizeof(time));
    int fleets = 0;
    for(int i = n-1; i >= 0; i--){
        ll p = ps[i];
        double pos = (double)(p>>32);
        double spe = (double)(p<<32>>32);
        time[i] = (target-pos)/spe;
        if(i<n-1&&time[i]<time[i+1]+0.00001)
            time[i] = time[i+1];
        else
            fleets++;
    }
    return fleets;
}
