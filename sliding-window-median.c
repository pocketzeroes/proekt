#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


typedef struct item {
    int val;
    struct item *next;
    struct item *prev;
} item_t;

item_t *items;
int size;
int head;
item_t *median;

double getMedian(void)
{  
    if ( size == 2 ) {
        return ((double)(items[0].val) + (items[1].val)) / 2.0;
    }
    if ( size % 2 == 0 ) {
      return ((double)median->val + median->next->val) / 2;
    } else {
      return median->val;
    } 
}
void slideWindow(int num)
{
    item_t *curr = median;
    head = (head + 1) % size;
    if ( items[head].val <= curr->val ) {
        median = curr->next;
    } 
    curr = median;
    items[head].next->prev = items[head].prev;
    items[head].prev->next = items[head].next;
    items[head].val = num;
    if ( num == curr->val ) {
        items[head].prev = curr;
        items[head].next = curr->next;
        curr->next->prev = items + head;
        curr->next = items + head;
        return ;
    }
    if ( num < curr->val ) {
        while ( num < curr->val )
            curr = curr->prev;
        items[head].prev = curr;
        items[head].next = curr->next;
        curr->next->prev = &items[head];
        curr->next = &items[head];
        median = median->prev;
        return ;
    }
    if ( num > curr-> val ) {
        while ( num > curr->val )
            curr = curr->next;
        items[head].prev = curr->prev;
        items[head].next = curr;
        curr->prev->next = &items[head];
        curr->prev = &items[head];
        return ;
    }
}
double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    double *ret;
    int i, nRetSize;
    item_t *min, *max, *tmp;
    nRetSize = numsSize - k + 1;
    *returnSize = nRetSize;
    ret = malloc(sizeof(double) * nRetSize);
    if ( k == 1 ) { 
        for ( i = 0; i < numsSize; i++ ) {
            ret[i] = (double)nums[i];
        }
        return ret;
    }
    items = malloc(sizeof(item_t) * k);
    size = k;
    head = k - 1;
    min = malloc(sizeof(item_t));
    min->val = INT_MIN;
    min->prev = NULL;
    max = malloc(sizeof(item_t));
    min->next = max;
    min->next->val = INT_MAX;
    min->next->next = NULL;
    min->next->prev = min;
    tmp = min;
    for ( i = 0; i < k; i++ ) {
        tmp = min;
        while ( tmp != NULL && tmp->val <= nums[i] ) {
            tmp = tmp->next;
        }
        if ( tmp == NULL )
            tmp = max;
        items[i].val = nums[i];
        items[i].next = tmp;
        items[i].prev = tmp->prev;
        tmp->prev->next = items + i;
        tmp->prev = items + i;
    }
    tmp = min;
    for ( i = 0; i < (k + 1) / 2; i++ ) {
        tmp = tmp->next;
    }
    median = tmp;
    for ( i = 0; i < nRetSize - 1; i++ ) {
        ret[i] = getMedian();
        slideWindow(nums[i + k]);
    }
    ret[nRetSize - 1] = getMedian();
    free(max);
    free(min);
    free(items);
    return ret;
}

#if 0
int main(void)
{
    //2147483647,1,2,3,4,5,6,7,2147483647
    // 2
    //1,3,-1,-3,5,3,6,7]
    //5
    //[1,3,-1,-3,5,3,6,7]
//3
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int nums2[] = {INT_MAX, 1, 2, 3, 4, 5, 6, 7, INT_MAX};
    int returnSize;
    int i;

    printf("Input: ");
    for ( i = 0; i < 8; i++ ) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    double *result = medianSlidingWindow(nums, 8, 3, &returnSize);
    for ( i = 0; i < returnSize; i++ ) {
        printf("%lf ", result[i]);
    }
    printf("\n");

    result = medianSlidingWindow(nums2, 9, 2, &returnSize);

    for ( i = 0; i < returnSize; i++ ) {
        printf("%lf ", result[i]);
    }
    printf("\n");
    free(result);

    return 0;
}
#endif