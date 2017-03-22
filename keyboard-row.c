#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char rowOne  [] = "qwertyuiop"; 
char rowTwo  [] = "asdfghjkl" ; 
char rowThree[] = "zxcvbnm"   ;



bool isInRow(char* word, char*row) {
    for( int i=0;word[i];i++ ){
        char c=word[i];
        char chr=tolower(c);
        if(strchr(row, chr)==NULL)
          return false;
    }
    return true;
}

char** findWords(char** words, int wordsSize, int* returnSize) {
    char** res=malloc(wordsSize*sizeof(char*));
    int resSize=0;
    for(int i=0;i<wordsSize;i++ ){
        char*word=words[i];
        if( isInRow(word, rowOne) || 
            isInRow(word, rowTwo) || 
            isInRow(word, rowThree) ){
               res[resSize++]=strdup(word);
        }
    }
    
    *returnSize=resSize;
    return res;
}

