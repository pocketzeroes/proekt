#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

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
typedef struct A
{
    struct A *prev;
    struct A *next;
    char*x;
}A;
/////////////////////////

void addingpar(A*, char*, int , int );


    A* res=NULL,*item;
char** generateParenthesis(int n, int* returnSize) {
    res=NULL;
    item=NULL;
    char niz[32]="";
    addingpar(res, niz, n, 0);
    int cnt;
    DL_COUNT(res, item, cnt);
    char**result=malloc(cnt*sizeof(char*));
    int resLen=0;
    DL_FOREACH(res, item) {
        result[resLen++] = item->x;
    }
    *returnSize=resLen;
    return result;
}
void addingpar(A*v, char* str, int n, int m){
    char*myc=strdup(str);
    char left [32];
    char right[32];
    sprintf(left, "%s%c",myc,')');
    sprintf(right,"%s%c",myc,'(');
    if(n==0 && m==0) {
        item = calloc(1, sizeof(A)); 
        item->x = myc;  
        DL_APPEND(res, item);        
//      puts(str);
        return;
    }
    if(m > 0){ addingpar(v, left , n  , m-1); }
    if(n > 0){ addingpar(v, right, n-1, m+1); }
}
#if 0
int main(){
    int len;
    char**rv=generateParenthesis(3,&len);
    for (int i=0;i<len;i++)
        puts(rv[i]);
}
#endif

