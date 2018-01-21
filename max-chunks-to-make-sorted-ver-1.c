int maxChunksToSorted(int*a, int aSz){
    int n = aSz;
    int reach = 0;
    int par = 0;
    for(int i = 0;i < n;i++){
        for(int j = reach;j <= i;j++){
            if(a[j] > i)
                goto outer;
        }
        reach = i;
        par++;
  outer:     ;
    }
    return par;
}
