#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>

typedef char* str;
void merge(str*a, int l, int m, int r){
  str tmp[r-l+5];
  int i = l, j = m + 1, k = 0;
  while(i<=m&&j<=r)
    tmp[k++] = strlen(a[i]) > strlen(a[j]) ? a[j++] : a[i++];
  while(i<=m)
    tmp[k++] = a[i++];
  while(j<=r)
    tmp[k++] = a[j++];
  for(int i = l,j=0; i <=r;)
    a[i++] = tmp[j++];
}
void mergesort(str*a, int l, int r){
  if(l>=r)
    return;
  int m = l + (r - l) / 2;
  mergesort(a, l, m);
  mergesort(a, m+1, r);
  merge(a, l, m, r);
}
char*words[100000];
int wsz;
char*arrangeWords(char*t){
  char*res = strdup(t);
  wsz=0;
  t[0] = tolower(t[0]);
  words[wsz++] = t;
  
  for(int z=0; t[z]; z++){char c=t[z];
    if(c==' '){
      t[z]='\0';
      words[wsz++] = t+z+1;
    }
  }
  mergesort(words, 0, wsz-1);
char*join(str*v){
  int i;
  res[0] = '\0';
  if(wsz==0)
    return res;
  strcat(res, v[0]);
  for(i=1; i<wsz; i++){
    strcat(res, " ");
    strcat(res, v[i]);
  }
  return res;
}
  char*str = join(words);
  str[0] = toupper(str[0]);
  return str;
}

// int main(){
//   puts(arrangeWords(strdup("Leetcode is cool")));
//   return 0;
// }
