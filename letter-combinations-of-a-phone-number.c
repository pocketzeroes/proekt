#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DL_APPEND(head,add)                                                                    \
    DL_APPEND2(head,add,prev,next)
#define DL_APPEND2(head,add,prev,next)                                                         \
do {                                                                                           \
  if (head) {                                                                                  \
      (add)->prev = (head)->prev;                                                              \
      (head)->prev->next = (add);                                                              \
      (head)->prev = (add);                                                                    \
      (add)->next = NULL;                                                                      \
  } else {                                                                                     \
      (head)=(add);                                                                            \
      (head)->prev = (head);                                                                   \
      (head)->next = NULL;                                                                     \
  }                                                                                            \
} while (0)

#define DL_FOREACH(head,el)                                                                    \
    DL_FOREACH2(head,el,next)
#define DL_FOREACH2(head,el,next)                                                              \
    for ((el) = (head); el; (el) = (el)->next)

#define DL_COUNT(head,el,counter)                                                              \
    DL_COUNT2(head,el,counter,next)                                                 
#define DL_COUNT2(head,el,counter,next)                                                        \
do {                                                                                           \
  (counter) = 0;                                                                               \
  DL_FOREACH2(head,el,next) { ++(counter); }                                                   \
} while (0)

        

char charmap[][5]= { " ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
typedef struct A
{
    struct A *prev;
    struct A *next;
    char*x;
}A;
char** letterCombinations(char* digits, int* returnSize) {
    if(strlen(digits)==0){
        *returnSize=0;
        char **rv=malloc(5);
        return rv;
    }
    A* res=NULL,*item,*it;
    int cnt;
    item = calloc(1, sizeof(A)); 
    item->x = "";  
    DL_APPEND(res, item);
    
    for (int i = 0; i < strlen(digits); i++)
    {
        A*tempres=NULL;
        char*chars = charmap[digits[i] - '0'];
        for (int c = 0; c < strlen(chars);c++)
        {
            DL_FOREACH(res, it) {
                char*buff=malloc(32);
                item = calloc(1, sizeof(A)); 
                sprintf(buff,"%s%c", it->x, chars[c]);
                item->x = buff;
                DL_APPEND(tempres,item); 
            }
        }
        res = tempres;
    }
    DL_COUNT(res, item, cnt);
    char**result=malloc(cnt*sizeof(char*));
    int resLen=0;
    DL_FOREACH(res, item) {
        result[resLen++] = item->x;
    }
    *returnSize=resLen;
    return result;
}
#if 0
int main(){
    int sz;
    letterCombinations("23",&sz);
    
}
#endif
