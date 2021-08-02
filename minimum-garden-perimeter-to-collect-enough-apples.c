typedef long long ll;

ll minimumPerimeter(ll neededApples){
  for(ll a=1;a<=10000000;a++){
    ll sum=a*(a+1)*(2*a+1)*2;
    if(sum>=neededApples)
      return a*8;
  }
  return-1;
}
