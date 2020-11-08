typedef long long ll;
enum{mod = 1000000007};
int cmp (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int maxProfit(int*inventory, int inventorySz, int orders){
  int n = inventorySz;
  qsort(inventory, inventorySz, sizeof(int), cmp);
  ll ret = 0;
  for(int i = n-1;i >= 0;i--){
    int can = inventory[i] - (i > 0 ? inventory[i-1] : 0);
    int use = fminl(orders, (ll)(n-i)*can);
    ll R = inventory[i];
    ll L = R - use/(n-i);
    ret += (R*(R+1)/2-L*(L+1)/2) * (n-i);
    ret += L*(use%(n-i));
    ret %= mod;
    orders -= use;
  }
  return(int)ret;
}
