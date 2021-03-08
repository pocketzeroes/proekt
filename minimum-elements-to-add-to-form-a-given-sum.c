typedef long long ll;

ll divup_L(ll a, ll b){
  return (a+b-1)/b;
}
int minElements(int*A, int Asz, ll L, ll T){
  int i;
  for(i=(0);i<Asz;i++){
    T -= A[i];
  }
  T = llabs(T);
  return(divup_L(T,L));
}
