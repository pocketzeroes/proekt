int countConsistentStrings(char*allowed, char**words, int wordsSz){
  bool ok[256];
  for(char (i)=('a');(i)<=('z');++(i))
    ok[i] = 0;
  for(int i=0; allowed[i]; ++i)
    ok[allowed[i]] = 1;
  int risan = 0;
  for(int i=0; i<wordsSz; ++i){
    for(int j=0; words[i][j];++j)
      if(!ok[words[i][j]])
        goto hell;
    ++risan;
    hell:;
  }
  return risan;
}
