#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}


typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmpP(const void*pa, const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}
int cmp(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int*ff=NULL;int ffSz=0;
int*ss=NULL;int ssSz=0;
pair*lin;

int upper_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}

int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid]) 
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}


int main() {
	int n;
    scanf("%d", &n);
	lin = malloc(n*sizeof(pair));
    int linSz=n;
    ll cum1[n+1];memset(cum1,0,sizeof(cum1));
    ll cum2[n+1];memset(cum2,0,sizeof(cum2));
	for (int i = 0; i<n; i++){
		scanf("%d %d", &lin[i].first, &lin[i].second);
		ff=pushback(ff, &ffSz, lin[i].first );
		ss=pushback(ss, &ssSz, lin[i].second);
	}
	qsort(ff , ffSz,sizeof(int) ,cmp);
	qsort(ss , ssSz,sizeof(int) ,cmp);
	qsort(lin,linSz,sizeof(pair),cmpP);
	for (int i = 0; i<n; i++) {
		if (!i)
            cum1[i] = ff[i], cum2[i] = ss[i];
		else {
			cum1[i] = cum1[i - 1] + ff[i];
			cum2[i] = cum2[i - 1] + ss[i];
		}
	}
	ll mn =(ll) 1e18;
	for (int i = 0; i<n; i++){
		ll tr1 = 0, tr2 = 0;
		int idx1 = lower_bound(ss, ssSz, lin[i].first);
		int idx2 = upper_bound(ff, ffSz, lin[i].first);
		tr1 = 1LL * (idx1)*lin[i].first - (idx1 == 0 ? 0 : cum2[idx1 - 1]);
		tr1 += cum1[n - 1] - (idx2 == 0 ? 0 : cum1[idx2 - 1]) - 1LL * (n - idx2)*lin[i].first;
		mn = min(mn, tr1);
		idx1 = lower_bound(ss, ssSz, lin[i].second);
		idx2 = upper_bound(ff, ffSz, lin[i].second);
		tr2 = 1LL * (idx1)*lin[i].second - (idx1 == 0 ? 0 : cum2[idx1 - 1]);
		tr2 += cum1[n - 1] - (idx2 == 0 ? 0 : cum1[idx2 - 1]) - 1LL * (n - idx2)*lin[i].second;
		mn = min(mn, tr2);
	}
	printf("%lld\n", mn);
	return 0;
}













































