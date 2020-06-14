int*finalPrices(int*prices, int pricesSz, int*rsz){
  int n = pricesSz;
  int*ret = calloc(n, sizeof(int));
  for(int i = 0;i < n;i++){
    ret[i] = prices[i];
    for(int j = i+1;j < n;j++){
      if(prices[j] <= prices[i]){
        ret[i] = prices[i] - prices[j];
        break;
      }
    }
  }
 *rsz=n;
  return ret;
}
