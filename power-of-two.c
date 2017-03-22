bool isPowerOfTwo (int x)
{
    if (x<0)return false;
  return ((x != 0) && !(x & (x - 1)));
}
