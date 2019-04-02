#include<stdio.h>
#include<stdlib.h>

typedef long long ll;

int leq(const void *a,const void *b){
	if ((*(ll*)a) - (*(ll*)b) > 0) return 1;
	if ((*(ll*)a) - (*(ll*)b) < 0) return -1;
	return 0;
}
ll log2(ll i){
	ll j = 2;
	ll r = 1;
	while (2*j <= i)
    j<<=1, r++;
	return r;
}
ll other[1000000];

int main(){
	ll n;
  scanf("%lld", &n);
  n--;
	ll me;
  scanf("%lld", &me);
	for(int i = 0; i < n; i++)
		scanf("%lld",other+i), other[i] = me - other[i];
	qsort(other,n,sizeof(ll),leq);
	ll d = other[0];
	int l = 0;
	while (other[l] == d && l < n)
    l++;
	int sl = 0;
	while (other[sl + l] - 1 == d && l + sl < n)
    sl++;
	ll steps = 1;
	ll s = 0;
	while(! (d == -1 || (d == 0 && l > 1))){
		if (l == 1){
			ll numStep = (sl+l < n) ? (other[sl+l] - steps - other[0]) : 100000000000000000LL;
			if(sl+l > 1 && numStep > d/log2(sl+l))
        numStep = d/log2(sl+l) - 1;
			if(numStep < 1)
        numStep = 1;
			steps+=numStep;
			if(l+sl > 1)
        s+=(1+log2(sl+l))*(numStep-1)+1;
      else
        s+= numStep;
			if(l+sl > 1)
        d-= (numStep-1) * log2(sl+l);
			l = l + sl;
			sl = 0;
			while(other[sl + l] - steps == other[0] && l + sl < n)
        sl++;
		}
    else {
			int ns = log2(l);
			if (ns > d)
        s+=d, d = -1;
			else
        d -= ns, s += ns;
			sl += l - 1;
			l = 1;
		}
	}
	printf("%lld\n",s);
	return 0;
}
