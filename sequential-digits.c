
int*sequentialDigits(int low, int high, int*rsz){
    int*ans = calloc(1000, sizeof(int));
    int asz = 0;
    for(int i=1; i<=9; ++i){
        for(int j=1; j+i-1<=9; ++j){
            int x=0;
            for(int k=0; k<i; ++k)
                x = x * 10 + (k + j);
            if(low<=x && x<=high)
                ans[asz++] = x;
        }
    }
   *rsz=   asz;
    return ans;
}
