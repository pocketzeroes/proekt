void reverse(char*str){
  if (str){
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end){
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
bool queryString(char*S, int N){
    if(N > 2400)
        return false;
    for(int i=1; i<=N; i++){
        char*str = strdup("");
        int x = i;
        while(x != 0){
            str = concatc(str, x%2+'0');
            x /= 2;
        }
        reverse(str);
        if(strstr(S, str) == NULL)
            return false;
    }
    return true;
}
