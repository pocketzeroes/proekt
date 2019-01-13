
enum {ARRSZ = 100005};
int  s    [ARRSZ];
bool oddok[ARRSZ],
    evenok[ARRSZ];

void add(int k, int v, int *s){
  k++;
  for(;k<ARRSZ;k+=-k&k)
    s[k]+=v;
}
int get(int k, int *s){
  if (k < 0)
    return 0;
  k++;
  int ans = 0;
  for(;k;k-=-k&k)
    ans += s[k];
  return ans;
}
int findkth(int k, int *s){
  int e = 0, cnt = 0;
  for(int i=20;i>=0;i--){
    int b = 1<<i;
    if(e+b>=ARRSZ || cnt+s[e+b]>=k)
      continue;
    e += b;
    cnt += s[e];
  }
  return e;
}
int oddEvenJumps(int*A, int Asz){
  memset(s,0,sizeof(s));
  memset(oddok, false,sizeof(oddok) );
  memset(evenok,false,sizeof(evenok));
  int n = Asz, ans = 1;
  evenok[A[n-1]] = oddok[A[n-1]] = true;
  add(A[n-1], 1, s);
  for (int i = n-2; i >= 0; i--) {
    int v = A[i];
    int cnt = get(100001, s) - get(v - 1, s);
    bool curodd = false,
         cureven = false;
    if (cnt > 0) {
      int j = findkth(get(v - 1, s) + 1, s);
      if (evenok[j])
        curodd = true;
    }
    cnt = get(v, s);
    if (cnt > 0) {
      int j = findkth(get(v, s), s);
      if (oddok[j])
        cureven = true;
    }
    oddok [A[i]] = curodd;
    evenok[A[i]] = cureven;
    if (curodd)
      ans++;
    add(A[i], 1, s);
  }
  return ans;
}
