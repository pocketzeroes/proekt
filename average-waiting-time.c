double averageWaitingTime(int**customers, int customersSz, int*customers0sz){
    double ans = 0;
    int end = 0;
    for(int z=0;z<customersSz;z++){int*v = customers[z];
        if(v[0] >= end){
            end = v[0] + v[1];
        }
        else{
            end += v[1];
        }
        ans += end - v[0];
    }
    return ans / customersSz;
}
