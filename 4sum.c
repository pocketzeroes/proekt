
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
    int*x;
}A;
int cmpfunc (const void * a, const void * b){    return ( *(int*)a - *(int*)b ); }

int** fourSum(int* num, int numsSize, int target, int* returnSize) {
    
    int len = numsSize;
    int left, right, sum;
    qsort(num, numsSize, sizeof(int),&cmpfunc);
    A* res=NULL,*item;
    int cnt;
    for (int i = 0; i < len - 3; ++i) {
        if (i && num[i] == num[i - 1]) {
            continue;
        }
        for (int j = i + 1; j < len - 2; ++j) {
            if (j != i + 1 && num[j] == num[j - 1]) {
                continue;
            }
            sum = target - num[i] - num[j];
            left = j + 1, right = len - 1;
            while (left < right) {
                if (num[left] + num[right] == sum) {
                    int*tmp=malloc(4*sizeof(int));
                    tmp[0]=num[i];
                    tmp[1]=num[j];
                    tmp[2]=num[left];
                    tmp[3]=num[right];
                    item = calloc(1, sizeof(A)); 
                    item->x = tmp;  
                    DL_APPEND(res, item);
                    ++left, --right;
                    while (left < right && num[left] == num[left - 1]) {
                        ++left;
                    }
                    while (left < right && num[right] == num[right + 1]) {
                        --right;
                    }
                } 
                else {
                    if (num[left] + num[right] > sum) {
                        --right;
                    } else {
                        ++left;
                    }
                }
            }
        }
    }
    DL_COUNT(res, item, cnt);
    char**result=malloc(cnt*sizeof(int*));
    int resLen=0;
    DL_FOREACH(res, item) {
        result[resLen++] = item->x;
    }
    *returnSize=resLen;
    return result;
}


