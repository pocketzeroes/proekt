#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef long long ll;

#ifdef _WIN32
char *strndup (const char *s, size_t n)
{
  char *result;
  size_t len = strlen (s);
  if (n < len)
    len = n;
  result = (char *) malloc (len + 1);
  if (!result)
    return 0;
  result[len] = '\0';
  return (char *) memcpy (result, s, len);
}
#endif
char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 


ll findb(char* s, ll Y){
  int ssize=strlen(s);
  ll lo = 10, hi =(ll) 1.1e18;
  while (lo < hi){
    ll b = (hi+lo+1)/2, cur = 0;
    if (pow(b, ssize-1)*(s[0]-'0') > Y + (ll)1e9){
      hi = b-1;
      continue;
    }
    for (int i = 0; i < ssize; i++)
      cur = (cur*b) + s[i]-'0';
    if (cur > Y)
      hi = b-1;
    else
      lo = b;
  }
  return lo;
}
char buff[10000];
char*concat(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s",a,b);
  return ptr;
}
char*string(int len, char c){
  char space[len+1]; memset(space, c, sizeof(space)); space[len]='\0';
  return strdup(space);
}
int main(){
  ll Y, b;
  char* L;
  scanf("%lld", &Y);
  scanf("%s", &buff);
  L = strdup(buff);
  int Lsize=strlen(L);
  do{
    for(int lp = Lsize-1;;){
      char*sub = substr(L, 0, lp+1);
      long long b1 = findb(concat(sub, string(Lsize-lp-1, '9')), Y);
      long long b2 = findb(concat(sub, string(Lsize-lp-1, '0')), Y);
      for (b = b2; b >= b1; b--){
        ll pb = 1, y;
        Lsize=strlen(L);
        for (int i = 0; i < Lsize - 1; i++)
          pb *= b;
        for (y = Y; pb; pb /= b){
          ll dig = y/pb;
          if (dig > 9)
            break;
          y -= dig*pb;
        }
        if (y == 0)
          goto done;
      }
      while(L[lp]++ == '9'){
        if(lp == 0)
          L = concat("0", L);
        else
          lp--;
      }
      Lsize=strlen(L);
    }
done:
    printf("%lld\n", b);
  }while(0);
}


























