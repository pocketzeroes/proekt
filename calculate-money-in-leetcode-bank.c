int a[1005];
int totalMoney(int n){
    int i,ans=a[0]=1;
    for(i=1;i<n;ans+=a[i++])if(i%7)a[i]=a[i-1]+1;
    else a[i]=a[i-7]+1;
    return ans;
}
