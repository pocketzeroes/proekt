void fill(bool*arr, int sz, bool val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
bool illustrate(int*lamp, int*loc){
    if(lamp[0] == loc[0] || lamp[1] == loc[1])
        return true;
    if(lamp[0] + lamp[1] == loc[0] + loc[1])
        return true;
    if(lamp[1] - lamp[0] == loc[1] - loc[0])
        return true;
    return false;
}
int*gridIllumination(int N, int**lamps, int lampsSz, int*lamps0sz, int**queries, int queriesSz, int*queries0sz, int*rsz){
    bool on[lampsSz];
    fill(on, lampsSz, true);
    int*res = calloc(queriesSz, sizeof(int));
    for(int i=0; i<queriesSz; i++){
        int*query = queries[i];
        int x = query[0], 
            y = query[1];
        for(int j = 0; j<lampsSz; j++){
            if(on[j] && illustrate(lamps[j], query)){
                res[i]=1;
                break;
            }
        }
        for(int j=0; j<lampsSz; j++){
            if(!on[j])
                continue;
            int*lamp = lamps[j];
            if(abs(query[0] - lamp[0]) <= 1 && 
               abs(query[1] - lamp[1]) <= 1){
                on[j] = false;
            }
        }
    }
   *rsz = queriesSz;
    return res;
}
