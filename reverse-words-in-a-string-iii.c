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
#define MAX_SZ 100000
char*reverseWords(char*s){
    char t  [MAX_SZ]={'\0'}; 
    char ans[MAX_SZ]={'\0'};int tLen=0;
    for(int i=0;s[i];i++){
        char c =s[i];
        if(c == ' ')
        {
            inplace_reverse(t);
            strcat(ans, t);
            strcat(ans, " ");
            memset(t,0,sizeof(t));tLen=0;
        }
        else
            t[tLen++] = c;
    }
    t[tLen]=0;
    inplace_reverse(t);
    strcat(ans,t);
    return strdup(ans);
}

