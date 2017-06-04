bool canPlaceFlowers(int*flowerbed, int flowerbedSz, int n){
    int m = 0, c = 1;
    for(int z=0;z<flowerbedSz;z++){int i=flowerbed[z];
        if (i == 0) 
            ++c;
        else {
            m += (c - 1) / 2;
            c = 0;
        }
    }
    ++c;
    m += (c - 1) / 2;
    return m >= n;
}
