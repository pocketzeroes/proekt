int a[100005];
int equalSubstring(char*s, char*t, int maxCost){
    int n = strlen(s),i,j,ans=0;
    for(i=0; i<n; i++)
        a[i+1] = a[i]+fmax(s[i]-t[i],t[i]-s[i]);
    for(i=1,j=0; i<=n; i++){
        for(;a[i]-a[j]>maxCost; j++);
        ans = fmax(ans, i-j);
    }
    return ans;
}
