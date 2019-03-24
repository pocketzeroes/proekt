typedef long long ll;
ll accumulate(int*arr, int sz){
  ll sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
bool canThreePartsEqualSum(int*A, int Asz){
    ll sum = accumulate(A, Asz);
    if(sum % 3 != 0)
        return false;
    ll running = 0;
    int times = 0;
    for(int i = 0; i < Asz; i++) {
        running += A[i];
        if (running == sum / 3) {
            running = 0;
            times++;
        }
    }
    return times >= 3;
}
