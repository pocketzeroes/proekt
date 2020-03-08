int numTimesAllBlue(int*light, int lightSz){
    int n=lightSz;
    int mx=0,ans=0;
    for(int i=0; i<n; i++){
        int x=light[i];
        mx = fmax(mx, x);
        if(mx==i+1)
            ans++;
    }
    return ans;
}
