typedef long long ll;
int N, K;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

void solve(int i, int pld, int val, vec*ans){
  if (i == N) {
    ans->ptr = pushback(ans->ptr, &ans->sz, val);
    return;
  }
  for(int t=0; t<2; t++){
    int d = t == 0 ? pld + K : pld - K;
    if(K == 0 && t == 1) 
      continue;
    if(0 <= d && d <= 9){
      solve(i+1, d, val*10 + d, ans);
    }
  }
}
int*numsSameConsecDiff(int _N, int _K, int*rsz){
  N = _N; 
  K = _K;
  vec ans = newVec();
  if(N == 1){
    for(int i=0; i<10; i++)
      ans.ptr = pushback(ans.ptr, &ans.sz, i);
    goto fin;
  }
  for(int s=1; s<10; s++)
    solve(1, s, s, &ans);
 fin:
 *rsz=   ans.sz;
  return ans.ptr;
}
