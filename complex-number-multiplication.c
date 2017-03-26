#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct pair{
    int first;
    int second;
}pair;

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
char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 


pair parse(char*a){
    pair result;
    int plus = strchr(a, '+') - a;
    int i    = strchr(a, 'i') - a;
    char*stra=substr(a, 0, plus);
    char*strb=substr(a, plus + 1, i - plus);
    int ra   = atoi(stra);
    int rb   = atoi(strb);
    result.first =ra;
    result.second=rb;
    return result;
}
char*complexNumberMultiply(char* a, char* b){
    pair av = parse(a);
    pair bv = parse(b);
    int ra = av.first * bv.first  - av.second * bv.second;
    int rb = av.first * bv.second + av.second * bv.first ;
    char*ptr;
    asprintf(&ptr,"%d+%di",ra,rb);
    return ptr;
}
#if 0
int main(){
  puts(complexNumberMultiply( "1+1i","1+1i"));
}
#endif















