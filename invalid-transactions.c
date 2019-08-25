#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
vecs TokenizeStr(char*s){
  vecs rez=newVecS();
  char n[55];
  for(int i=0;i<4;i++){
    sscanf(s, "%[a-z 0-9]", &n);
    rez.ptr = pushbackS(rez.ptr, &rez.sz, strdup(n));
    s = strchr(s, ',');
    s++;
  }
  return rez;
}
char**invalidTransactions(char**transactions, int transactionsSz, int*rsz){
    vecs V[transactionsSz];
    for(int i=0; i<transactionsSz; i++){
        V[i] = TokenizeStr(strdup(transactions[i]));
    }
    vecs R = newVecS();
    int x,y;
    for(x=0; x<transactionsSz; x++){
        int valid=1;
        int tim=atoi(V[x].ptr[1]);
        int val=atoi(V[x].ptr[2]);
        if(val>1000)
            valid=0;
        for(y=0; y<transactionsSz; y++) 
            if(x!=y){
                int tim2 = atoi(V[y].ptr[1]);
                if(strcmp(V[x].ptr[0], V[y].ptr[0])==0 &&strcmp(V[x].ptr[3], V[y].ptr[3])!=0 && abs(tim-tim2)<=60)
                    valid=0;
            }
        if(valid==0)
            R.ptr=pushbackS(R.ptr, &R.sz, transactions[x]);
//        else puts("valid");
    }
   *rsz =  R.sz;
    return R.ptr;
}
