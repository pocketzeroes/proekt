#define swap(a,b) do{ __typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
void erase(char*v, int vsz, int pos){
  for(int i=pos; i<vsz-1; i++)
    v[i] = v[i+1];
//(v->sz)--;
}
bool checkPalindromeFormation(char*a, char*b){
  int bahur;
  int i;
  int x;
  int y;
  int n = strlen(a);
  int aa;
  int ba;
  int bb;
  int naa;
  int nba;
  int nbb;
  if(n % 2){
    erase(a, n, n/2);
    erase(b, n, n/2);
    n--;
  }
  for(bahur=0; bahur<2; bahur++){
    swap(a, b);
    aa = ba = bb = 1;
    for(i=(0); i<(n/2); i++){
      x = n/2 - 1 - i;
      y = n/2 + i;
      naa = nba = nbb = 0;
      if(aa && a[x] == a[y]){
        naa = 1;
      }
      if(bb && b[x] == b[y]){
        nbb = 1;
      }
      if((aa || ba || bb) && b[x] == a[y]){
        nba = 1;
      }
      {
        int nacepin = (naa);
        int vafla   = (nba);
        int mura    = (nbb);
        aa = nacepin;
        ba = vafla;
        bb = mura;
      }
    }
    if(aa || ba || bb){
      return true;
    }
  }
  return false;
}
