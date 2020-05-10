
int countTriplets(int*arr, int arrSz){
    int ret=0;
    int x,y,z;
    int N=arrSz;
    for(x=0;x<N;x++){
        int a=0;
        for(y=x;y<N;y++){
            a^=arr[y];
            int b=0;
            for(z=y+1;z<N;z++){
                b^=arr[z];
                if(a==b)
                    ret++;
            }
        }
    }
    return ret;
}
