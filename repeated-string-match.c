char*concat(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  free(a);
  return ptr;
}

int repeatedStringMatch(char*A, char*B){
    char*ker = strdup("");
    int An = strlen(A);
    int Bn = strlen(B);
    while(strlen(ker) < An+Bn)
        ker = concat(ker, A);
    for(int i = 0; i < An; ++i){
        bool suc=1;
        for(int j=0; j<Bn; j++){
            if(ker[i+j] != B[j]){
                suc=0;
                break;
            }
        }
        if(suc)
            return (i+Bn+An-1)/An;
    }
    return -1;
}
