#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
typedef char* string;

int cmp(const void*pa,const void*pb){
  char*a=(char*)pa;
  char*b=(char*)pb;
  return a[0]-b[0];
}
#define MAX_LEN 100000
char gword[MAX_LEN];
char res  [MAX_LEN];
int main() {
    int n;
    scanf("%d", &n);
    string words[n];
    for(int i = 0; i < n; ++i){
        scanf("%s", &gword);
        words[i]=strdup(gword);
    }

    int resLen=0;
    for(int i=0;i<n;i++){
        char*word=words[i];
        char smallestLetter=word[0];
        for(int z=0;word[z];z++){
            char letter=word[z];
            smallestLetter = min(smallestLetter, letter);
        }
        res[resLen++] = smallestLetter;
    }
    res[resLen]='\0';
    qsort(res, resLen, sizeof(char), cmp);
    puts(res);
}


