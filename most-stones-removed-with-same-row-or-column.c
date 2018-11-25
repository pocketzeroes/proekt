
int rep[1005];
int find(int x) {
  if(rep[x] == x)
    return x;
  else{
    int rv = find(rep[x]);
    rep[x] = rv;
    return rv;
  }
}
void Union(int x, int y) {
  int rx = find(x), 
      ry = find(y);
  if (rx == ry)
    return;
  rep[rx] = ry;
}

int removeStones(int**st, int stSz, int*st0sz){
  int n = stSz;
  for(int i=(0);i<(n);i++)
    rep[i] = i;
  for(int i=(0);i<(n);i++){
    for(int j=(i+1);j<(n);j++){
      if (st[i][0] == st[j][0] || st[i][1] == st[j][1])
        Union(i, j);
    }
  }
  int ans = 0;
  for(int i=(0);i<(n);i++)
    if (find(i) == i)
      ans++;
  return n - ans;
}
