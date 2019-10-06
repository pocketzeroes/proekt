int minCostToMoveChips(int*chips, int chipsSz){
    int l = 0, r = 0;
    for(int z=0;z<chipsSz;z++){int x = chips[z];
        if (x % 2 == 0)
            l++;
        else
            r++;
    }
    return fmin(l, r);
}
