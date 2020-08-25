void reverse(char*str){
  if(str){
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while(str < end){
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

char res[100000];
int rsz;
char*thousandSeparator(int n){
  rsz=0;
  if(n==0)
    return strdup("0");
  for(;;){
    res[rsz++] = (char)('0' + n%10);
    n /= 10;
    if(n==0)
      break;
    if(rsz%4==3)
      res[rsz++] = '.';
  }
  res[rsz]='\0';
  reverse(res);
  return strdup(res);
}
