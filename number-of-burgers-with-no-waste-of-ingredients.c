int*numOfBurgers(int tomatoSlices, int cheeseSlices, int*rsz){
    int*rv=calloc(2, sizeof(int));
    int x = tomatoSlices-2*cheeseSlices;
    if(x%2!=0){
        *rsz=0;
        return rv;
    }
    int jumbo = x / 2;
    int small = cheeseSlices - jumbo;
    if(jumbo < 0 || small < 0){
        *rsz=0;
        return rv;
    }
    *rsz=2;
    rv[0]=jumbo;
    rv[1]=small;
    return rv;
}
