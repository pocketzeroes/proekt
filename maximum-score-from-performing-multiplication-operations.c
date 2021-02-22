typedef long long ll;
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

ll dp[1005];
ll ndp[1005];

int maximumScore(int*nums, int numsSz, int*multipliers, int multipliersSz){
  int n = numsSz;
  int m = multipliersSz;
  fill(dp, m+1, (ll)-1e18);
  dp[0] = 0;
  int use = 0;
  for(int z=0;z<m;z++){int out=multipliers[z];
    fill(ndp, m+1, (ll)-1e18);
    for(int i=0; i<=use; i++){
      ndp[i+1] = fmaxl(ndp[i+1], dp[i] + nums[i] * out);
      ndp[i] = fmaxl(ndp[i], dp[i] + nums[n-1-(use-i)] * out);
    }
    for(int a=0; a<=m; a++){
      dp[a] = ndp[a];
    }
    use++;
  }
  ll ret = (ll)-1e18;
  for(int i=0; i<=m; i++){
    ret = fmaxl(ret, dp[i]);
  }
  return ret;
}
