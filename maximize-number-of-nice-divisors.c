typedef long long ll;
const ll mo=1000000007;

ll modpow(ll a, ll n){
	ll r=1;
  a%=mo;
	while(n)
    r=r*((n%2)?a:1)%mo,a=a*a%mo,n>>=1;
	return r;
}
int maxNiceDivisors(int primeFactors){
  if(primeFactors<=4)
    return primeFactors;
  if(primeFactors%6==1){
    ll pat=12*modpow(9,(primeFactors-7)/6)%mo;
    return pat;
  }
  else{
    ll pat=modpow(9,primeFactors/6);
    primeFactors%=6;
    if(primeFactors>=1&&primeFactors<=4)
      pat*=primeFactors;
    if(primeFactors==5)
      pat*=6;
    return pat%mo;
  }
}
