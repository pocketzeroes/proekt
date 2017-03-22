char result[12001]={'\0'};
void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

char* convertToTitle(int n) {
    memset(result,0,sizeof(result));
    int   resultLen=0;
    int   dvd=n;
    while (dvd) {
        result[resultLen++]=(dvd - 1) % 26 + 'A';
        dvd = (dvd - 1) / 26;
    }
    inplace_reverse(result);
    return result;
}
