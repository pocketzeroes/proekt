int cmp (const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int minDeletions(char*s){
  int i;
  int res = 0;
  int f[26]={};
  for(i=(0);s[i];i++){
    f[s[i]-'a']++;
  }
  qsort(f, 26, sizeof(int), cmp);
  for(;;){
    for(i=(0);i<(25);i++){
      if(f[i] && f[i]==f[i+1]){
        f[i]--;
        res++;
        goto Q5VJL1cS;
      }
    }
    break;
  Q5VJL1cS:;
  }
  return res;
}
