
bool present[1 << 20];

bool hasAllCodes(char*s, int k){
  for(int i=0; i<(1<<k); i++)
    present[i] = false;
  int amt  = 0;
  int curr = 0;
  for(int i = 0; s[i]; i++){
    if(i >= k && s[i-k] == '1')
      curr -= (1 << (k-1));
    curr *= 2;
    curr += s[i] == '1';
    if(i >= k-1 && !present[curr]){
      present[curr] = true;
      amt++;
    }
  }
  return amt == (1 << k);
}
