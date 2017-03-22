#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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



bool check(char* s, int pos, int len1, int len2)
{
    int start = pos+len1+len2;
    if(start == strlen(s)) {
        if(pos==0) 
            return false; 
        return true;
    }
    int minLen = max(len1, len2);
    if((s[pos]=='0'&&len1>1) || (s[pos+len1]=='0'&&len2>1)) 
        return false;
    long num1 = atol(substr(s,pos, len1) ); 
    long num2 = atol(substr(s,pos+len1, len2) );
    if(num1>INT_MAX || num2>INT_MAX) 
        return false;
    for(int l = minLen; l <= strlen(s)-start; ++l)
    {
        if(l>1 && s[start]=='0') 
            return false;
        long num3 = atol(substr(s,start, l) );
        if(num3 > num1+num2) 
            return false;
        if(num3==num1+num2 && check(s, pos+len1, len2, l)) 
            return true; 
    }
    return false;
}
bool isAdditiveNumber(char* s) 
{
    int len = strlen(s);
    for(int l1 = 1; l1 <= len/2; ++l1)
        for(int l2 = 1; l2 < len-max(l1, l2); ++l2)
            if(check(s, 0, l1, l2)) 
                return true;
    return false;
}























