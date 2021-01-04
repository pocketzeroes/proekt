enum{SZ = 1 << 17};
int tree[2 * SZ];

void upd(int idx, int val){
  idx += SZ;
  tree[idx] = val;
  while(idx > 1){
    idx /= 2;
    tree[idx] = fmax(tree[2*idx], tree[2*idx+1]);
  }
}
int qry(int lhs, int rhs){
  int ret =(int)-2e9;
  lhs += SZ;
  rhs += SZ;
  while(lhs <= rhs){
    if(lhs%2) ret = fmax(ret, tree[lhs++]);
    if(rhs%2==0) ret = fmax(ret, tree[rhs--]);
    lhs /= 2;
    rhs /= 2;
  }
  return ret;
}
int maxResult(int*nums, int numsSz, int k){
  int n = numsSz;
  upd(0, nums[0]);
  for(int i = 1; i < n; i++){
    int lhs = fmax(0, i-k);
    upd(i, qry(lhs, i-1) + nums[i]);
  }
  return qry(n-1, n-1);
}
