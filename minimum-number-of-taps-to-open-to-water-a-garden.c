typedef struct{
  int first, second;
}pair;
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
enum{ INF =(int) 1e9 + 5};

int minTaps(int n, int*ranges, int rangesSz){
    pair intervals[n+1];
    for(int i=0; i<=n; i++)
        intervals[i] = (pair){fmax(i - ranges[i], 0), fmin(i + ranges[i], n)};
    qsort(intervals, n+1, sizeof(pair), cmpP);
    int dp[n+1]; fill(dp, n+1, INF);
    int best = INF;
    for(int i=n; i>=0; i--){
        if(intervals[i].second >= n)
            dp[i] = 1;
        for(int j=i+1; j<=n; j++)
            if(intervals[i].second >= intervals[j].first)
                dp[i] = fmin(dp[i], dp[j] + 1);
        if(intervals[i].first <= 0)
            best = fmin(best, dp[i]);
    }
    return best < INF ? best : -1;
}
