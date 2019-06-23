bool carPooling(int**trips, int tripsSz, int*trips0sz, int capacity){
    int imos[1005]={0};
    for(int z=0;z<tripsSz;z++){int*t = trips[z];
        imos[t[1]] += t[0];
        imos[t[2]] -= t[0];
    }
    for(int i = 0;i < 1001;i++){
        imos[i+1] += imos[i];
    }
    for(int i = 0;i < 1001;i++){
        if(imos[i] > capacity){
            return false;
        }
    }
    return true;
}
