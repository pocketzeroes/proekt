#include<stdio.h>
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
char * substr(const char *str, int start, int end) {
  if (0 > start)     return NULL;
  int len = strlen(str);
  if (-1 == end) end = len;
  if (end <= start)  return NULL;
  int diff = end - start;
  if (len == diff)   return strdup(str);
  if (len < start)   return NULL;
  if (len + 1 < end) return NULL;
  char *res = malloc(sizeof(char) * diff + 1);
  if (NULL == res)   return NULL;
  memset(res, '\0', diff + 1);
  strncpy(res, str + start, diff);
  return res;
}

char* shortestPalindrome(char* s) {
    int slen=strlen(s);
    if (slen==0)return s;
    char* rev_s = strdup(s);
    inplace_reverse(rev_s);
    char l[slen*2+2];memset(l,0,sizeof(l));
    sprintf(l,"%s#%s",s,rev_s);
    int llen=strlen(l);
    int p[slen*2+2];memset(p,0,sizeof(p));
    for (int i = 1; l[i] ; i++) {
        int j = p[i - 1];
        while (j > 0 && l[i] != l[j])
            j = p[j - 1];
        p[i] = (j += l[i] == l[j]);
    }
    char buff[199024];
    char*rez=substr(rev_s, 0, slen - p[llen - 1]);
    if(rez){
        sprintf(buff,"%s%s",rez, s);
        return  strdup(buff);
    }
    else
        return s;
}
