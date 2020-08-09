bool b[2005];
int findKthPositive(int*arr, int arrSz, int k){
    memset(b,0,sizeof(b));
    int i;
    for(int z=0;z<arrSz;z++){int a=arr[z];
        b[a]=1;
    }
    for(i=1;;i++)
        if(!b[i]){
            k--;
            if(!k)
                break;
        }
    return i;
}
