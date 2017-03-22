#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>




bool is_vowel(char a){
    switch(a){
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u':return true;
    }
    return false;
}

char* reverseVowels(char* param) {
    char*s=strdup(param);
    for(int i = 0, j = strlen(s) - 1; i < j; ){
        if (!is_vowel(tolower(s[i]))) 
            ++i;
        else if (!is_vowel(tolower(s[j])))
            --j;
        else{
          char a = s[i];
          char b = s[j];
          s[i++]=b;
          s[j--]=a;
        }
    }
    return s;
}

int main(){
    puts(reverseVowels("leetcode"));
}

