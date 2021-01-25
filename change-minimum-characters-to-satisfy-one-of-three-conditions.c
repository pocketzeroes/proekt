int chmin(int*a, int b){
  if(*a>b)
    *a=b;
  return*a;
}
int minCharacters(char*a, char*b){
  int a_size=strlen(a);
  int b_size=strlen(b);
  int i;
  int res = 1073709056;
  int tmp;
  int cntA[26] = {};
  int cntB[26] = {};
  for(i=(0);a[i];i++){
    cntA[a[i]-'a']++;
  }
  for(i=(0);b[i];i++){
    cntB[b[i]-'a']++;
  }
  for(i=(0);i<(26);i++){
    chmin(&res, a_size+b_size - cntA[i] - cntB[i]);
  }
  for(i=(1);i<(26);i++){
    int j;
    tmp = 0;
    for(j=(0);j<(i);j++){
      tmp += cntA[j];
    }
    for(j=(i);j<(26);j++){
      tmp += cntB[j];
    }
    chmin(&res, tmp);
  }
  for(i=(1);i<(26);i++){
    int j;
    tmp = 0;
    for(j=(0);j<(i);j++){
      tmp += cntB[j];
    }
    for(j=(i);j<(26);j++){
      tmp += cntA[j];
    }
    chmin(&res, tmp);
  }
  return res;
}
