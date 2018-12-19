int D[31][1<<8];

int*prisonAfterNDays(int*cells, int cellsSz, int N, int*rsz){
  memset(D, -1, sizeof D);
  for(int s=0, s_len=(1<<8); s<s_len; ++s) {
      int ns = 0;
      for (int i=1; i<7; i++) {
        int c = (s>>(i-1)&1) + (s>>(i+1)&1);
        if (c == 0 || c == 2)
          ns |= 1<<i;
      }
      D[0][s] = ns;
  }
  for(int t=0, t_len=(30); t<t_len; ++t)
    for(int s=0, s_len=(1<<8); s<s_len; ++s)
      D[t+1][s] = D[t][D[t][s]];
  int s = 0;
  for(int i=0, i_len=(8); i<i_len; ++i)
    s |= cells[i] << i;
  for(int i=0, i_len=(31); i<i_len; ++i)
    if (N>>i&1)
      s = D[i][s];
  int*ret = calloc(8, sizeof(int));
  for(int i=0, i_len=(8); i<i_len; ++i)
    ret[i] = s>>i&1;
 *rsz = 8;
  return ret;
}
