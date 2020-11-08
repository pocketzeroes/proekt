enum{SZ = 1 << 17};
int tree[2 * SZ];
void upd(int idx, int val){
  idx += SZ;
  while(idx){
    tree[idx] += val;
    idx /= 2;
  }
}
int qry(int lhs, int rhs){
  lhs += SZ;
  rhs += SZ;
  int ret = 0;
  while(lhs <= rhs){
    if(lhs%2) ret += tree[lhs++];
    if(rhs%2==0) ret += tree[rhs--];
    lhs /= 2;
    rhs /= 2;
  }
  return ret;
}
int createSortedArray(int*instructions, int instructionsSz){
  int ret = 0;
  for(int z=0;z<instructionsSz;z++){int out=instructions[z];
    int lhs = qry(0, out-1);
    int rhs = qry(out+1, SZ-1);
    ret += fmin(lhs, rhs);
    ret %= 1000000007;
    upd(out, 1);
  }
  for(int z=0;z<instructionsSz;z++){int out=instructions[z];
    upd(out, -1);
  }
  return ret;
}
