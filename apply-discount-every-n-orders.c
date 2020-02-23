typedef struct {
}Cashier;
Cashier*gptr;

int n,discount,cnt;
double*ps;

Cashier*cashierCreate(int n_, int dis, int*products, int productsSz, int*prices, int pricesSz){
  n=n_;
  discount=100-dis;
  cnt=0;
  ps=calloc(300, sizeof(double));
  for(int i=0; i<productsSz; i++)
    ps[products[i]]=prices[i];
  return gptr;
}
double cashierGetBill(Cashier*obj, int*product, int productSz, int*amount, int amountSz){
  double res=0;
  int m=productSz;
  for(int i=0; i<m; i++)
    res+=ps[product[i]]*amount[i];
  cnt++;
  if(cnt==n){
    res*=discount;
    res/=100;
    cnt=0;
  }
  return res;
}
void cashierFree(Cashier*obj){
  ;
}
