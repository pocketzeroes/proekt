char*restoreString(char*s, int*indices, int indicesSz){
  char*T = strdup(s);
  for(int i=0; s[i]; i++)
    T[indices[i]] = s[i];
  return T;
}
