void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int*upper;
int upperSz;
void newDJSet(int n){
  upperSz = n;
  upper = calloc(n, sizeof(int));
  fill(upper, n, -1);
}
int root(int x){
  return upper[x] < 0 ? x : (upper[x] = root(upper[x]));
}
bool equiv(int x, int y){
  return root(x) == root(y);
}
bool ds_union(int x, int y){
  x = root(x);
  y = root(y);
  if (x != y) {
    if (upper[y] < upper[x]) {
      int d = x;
      x = y;
      y = d;
    }
    upper[x] += upper[y];
    upper[y] = x;
  }
  return x == y;
}
int count(){
  int ct = 0;
  for(int z=0;z<upperSz;z++){int u = upper[z];
    if (u < 0)
      ct++;
  }
  return ct;
}
bool equationsPossible(char**equations, int eqSz){
    newDJSet(26);
    for(int z=0;z<eqSz;z++){char*e = equations[z];
        if(e[1] == '='){
            int l = e[0]-'a';
            int r = e[3]-'a';
            ds_union(l, r);
        }
    }
    for(int z=0;z<eqSz;z++){char*e = equations[z];
        if(e[1] == '!'){
            int l = e[0]-'a';
            int r = e[3]-'a';
            if(equiv(l, r)){
                return false;
            }
        }
    }
    return true;
}
