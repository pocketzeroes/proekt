int*closestDivisors(int num, int*rsz){
    int*ans=calloc(2, sizeof(int));
    for(int i=1;i*i<=num+2;i++){
        if((num+2)%i==0){
            ans[0]=i;
            ans[1]=(num+2)/i;
        }
        if((num+1)%i==0){
            ans[0]=i;
            ans[1]=(num+1)/i;
        }
    }
   *rsz=2;
    return ans;
}
