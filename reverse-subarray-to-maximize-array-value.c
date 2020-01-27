typedef long long ll;

int maxValueAfterReverse(int*a, int aSz){
    ll sum = 0;
    for(int i=1; i<aSz; ++i)
        sum += llabs(a[i]-a[i-1]);
    ll ans = sum;
    for(int i=2; i<aSz; ++i){
        ans = fmaxl(ans, sum-llabs(a[i]-a[i-1])+llabs(a[0]-a[i]));
    }
    for(int i=0; i<aSz-1; ++i){
        ans = fmaxl(ans, sum-llabs(a[i]-a[i+1])+llabs(a[i]-a[aSz-1]));
    }
    int n = aSz;
    ll mx;
    mx = -1e9;
    for(int i=1; i<n; ++i){
        ans = fmaxl(ans, sum+mx+a[i-1]-a[i]-llabs(a[i-1]-a[i]));
        mx  = fmaxl(mx, -a[i-1]+a[i]-llabs(a[i-1]-a[i]));
    }
    mx = -1e9;
    for(int i=1; i<n; ++i){
        ans = fmaxl(ans, sum+mx-a[i-1]-a[i]-llabs(a[i-1]-a[i]));
        mx  = fmaxl(mx, +a[i-1]+a[i]-llabs(a[i-1]-a[i]));
    }
    mx = -1e9;
    for(int i=1; i<n; ++i){
        ans = fmaxl(ans, sum+mx+a[i-1]+a[i]-llabs(a[i-1]-a[i]));
        mx  = fmaxl(mx, -a[i-1]-a[i]-llabs(a[i-1]-a[i]));
    }
    mx = -1e9;
    for(int i=1; i<n; ++i){
        ans = fmaxl(ans, sum+mx-a[i-1]+a[i]-llabs(a[i-1]-a[i]));
        mx  = fmaxl(mx, +a[i-1]-a[i]-llabs(a[i-1]-a[i]));
    }
    return ans;
}
