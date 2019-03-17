
int bitwiseComplement(int N){
  if (!N)
    return 1;
  int lastbit = 31 - __builtin_clz(N);
  int ret = 0;
  for (int i = lastbit; i >= 0; --i)
    if (!(N & (1 << i)))
      ret |= 1 << i;
  return ret;
}
