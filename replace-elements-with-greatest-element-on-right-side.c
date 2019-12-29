int*replaceElements(int*arr, int arrSz, int*rsz){
    int ma=-1,i;
    for(i=arrSz-1; i>=0; i--){
        int x = arr[i];
        arr[i] = ma;
        ma = fmax(ma,x);
    }
   *rsz=arrSz;
    return arr;
}
