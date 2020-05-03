
char*destCity(char***paths, int pathsSz, int*paths0sz){
  int N = pathsSz;
  for(int i=0; i<N; ++i){
    char*t = strdup(paths[i][1]);
    bool ok = true;
    for(int j=0; j<N; ++j){
      if(strcmp(paths[j][0], t)==0){
        ok = false;
        break;
      }
    }
    if(ok)
      return t;
  }
  return strdup("");
}
