#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#ifndef _WIN32
char *strrev(char *str)
{
    if(str[1]=='\0')return str;
    char *p1, *p2;
    if (! str || ! *str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}
#endif

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
int maxi(int a,int b){return a>b?a:b;}
char*max(char*a,char*b){return strcmp(a,b)>0?a:b;}





int gSz;

char* optimize(char** strs, int ind, char* start, char* end) {
    char ret[1000];
    strcpy(ret, start);
    for(int i=(ind+1)% gSz; i != ind; i = (i+1) % gSz) {
        char* rev;
        rev = strdup(strs[i]);
        strrev(rev);
        if(strcmp(rev , strs[i])>0) strcat(ret , rev    );
        else                        strcat(ret , strs[i]);
        free(rev);
    }
    strcat(ret , end);
    return strdup(ret);
}
char* splitLoopedString(char**new_strs, int ssize){
    gSz=ssize;
    char*ans = strdup("$");
    for(int i=0; i<ssize; i++) {
        int len = strlen(new_strs[i]);
        for(int j=0; j<=len; j++) {
            for(int k=0; k<2; k++) {
                char* th;
                char* front;
                char* end;
                front = substr(new_strs[i], 0, j);
                end   = substr(new_strs[i], j, len-j);
                th    = optimize(new_strs, i, end, front);
                if(strcmp(ans, th)<0){
                    free(ans);
                    ans = th;
                }
                else{
                    free(th);
                }
                strrev(new_strs[i]);
                free(front);
                free(end);
            }
        }
    }
    return ans;
}




#ifdef _WIN32
int main(){
    int asz=2;
    char**arr=malloc(asz*sizeof(char*));
//#include "test.c"
    arr[0]=strdup("abc");
    arr[1]=strdup("xyz");
    
    puts( splitLoopedString(arr, asz));
}
#endif




























