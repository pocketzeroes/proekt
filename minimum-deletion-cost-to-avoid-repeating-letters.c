typedef long long ll;
#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)
#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)

void amin(int*x, int y){
    if(y<*x)
       *x=y;
}
ll min_element(ll*arr, ll sz){
  ll mine = arr[0];
  for(ll i=1;i<sz;i++)
    if(arr[i]<mine)
      mine=arr[i];
  return mine;
}
ll buf[2][26];
ll*cur = buf[0];
ll*nxt = buf[1];

int minCost(char*s, int*cost, int costSz){
    memset(cur, 0, sizeof buf[0]);
    int s_size = strlen(s);
    REP(i, s_size){
        memset(nxt, 0x3f, sizeof buf[0]);
        REP(c, 26){
          amin(&nxt[c], cur[c] + cost[i]);
          if(s[i] != c + 'a'){
            amin(&nxt[s[i] - 'a'], cur[c]);
          }
        }
        swap(cur, nxt);
    }
    ll ans = min_element(cur, 26);
    return ans;
}
