int*shuffle(int*nums, int numsSz, int n, int*rsz){
    int*a = calloc(2*n, sizeof(int));
    for(int i=0; i<n*2; i++){
        a[i] = i % 2 == 0 ? nums[i/2] : nums[i/2+n];
    }
   *rsz=2*n;
    return a;
}
