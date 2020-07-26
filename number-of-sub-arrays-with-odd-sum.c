

#define MD (1000000007U)

int s[100000+2];

int numOfSubarrays(int*arr, int arrSz){
  int i;
  long long N = arrSz;
  long long res = 0;
  long long c[2] = {};
  for(i=(0);i<(N);i++){
    s[i+1] = (s[i] + arr[i]) % 2;
  }
  for(i=(0);i<(N+1);i++){
    res += c[s[i]^1];
    c[s[i]]++;
  }
  return res % MD;
}
