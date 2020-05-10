
char**buildArray(int*target, int targetSz, int n, int*rsz){
  int is[101]={};
  for(int z=0; z<targetSz; z++){int t=target[z];
    is[t]=1;
  }
  char**T=calloc(10000, sizeof(char*));
  int tsz=0;
  for(int i=1; i<=n; i++){
    T[tsz++]=strdup("Push");
    if(is[i]==0)
      T[tsz++]=strdup("Pop");
    if(target[targetSz-1]==i)
      break;
  }
 *rsz=tsz;
  return T;
}
