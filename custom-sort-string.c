char*s;
int Tlen;
int pcmp(const void*pa, const void*pb){
  char*pc1=(char*)pa;
  char*pc2=(char*)pb;
  char c1= *pc1;
  char c2= *pc2;
  int i1,i2;
  for(i1=0; i1<Tlen; i1++)
    if(s[i1]==c1) 
      break;
  for(i2=0; i2<Tlen; i2++)
    if(s[i2]==c2)
      break;
  return(i1<i2)?-1:1;
}
char*customSortString(char*ss, char*T){
  s = ss;
  Tlen = strlen(T);
  qsort(T, Tlen, sizeof(char), pcmp);
  return T;
}
