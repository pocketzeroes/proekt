#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_SWAP(a, b) {\
                        int temp = *(a);\
                        *(a) = *(b);\
                        *(b) = temp;\
                        }

#define MAX_STR_SZ 16

int CompareStr(char *s1, char *s2)
{
    char *ts1 = s1, *ts2 = s2;
    while (*ts1 || *ts2)
        if (*ts1 && *ts2) {
            if (*ts1 == *ts2) {
                ts1++;
                ts2++;
            }
            else if (*ts1 != *ts2)
                break;
        }
        else if (*ts1)
            ts2 = s2;
        else
            ts1 = s1;
    return (int)(*ts1 - *ts2);
}

int GetPivot(char **s, int start, int end)
{
    int i = start, j = end - 1, pivot = end;
    while (i <= j)
    {
        if (i < end && CompareStr(s[i], s[pivot]) > 0)
            i++;
        if (j >= start && CompareStr(s[j], s[pivot]) < 1)
            j--;
        if (i < j)
            INT_SWAP((int *)&s[i], (int *)&s[j]);
    }
    INT_SWAP((int *)&s[i], (int *)&s[pivot]);
    return i;
}

void QuickSort(char **s, int start, int end)
{
    int pivot;
    if (start >= end)
        return;
    pivot = GetPivot(s, start, end);
    QuickSort(s, start, pivot - 1);
    QuickSort(s, pivot + 1, end);
}

char *largestNumber(int* nums, int numsSize)
{
    int i, ssize = 0, slen;
    char *ch     = NULL, *tch;
    char **cstr  = NULL;
    if (!nums || numsSize < 1 || !(cstr = malloc( numsSize * sizeof(char *) + (numsSize * MAX_STR_SZ))))
        goto bahur;
    tch = (char *)(cstr + numsSize);
    for (i = 0; i < numsSize; ++i){
        cstr[i] = tch; 
        if (!(slen = sprintf(cstr[i],"%d",nums[i])))
            goto bahur;
        tch   += MAX_STR_SZ; 
        ssize += slen;
    }
    QuickSort(cstr, 0, numsSize - 1);
    if (!(ch = malloc(sizeof(char) * (ssize + 1))))
        goto bahur;
    strcpy(ch, cstr[0]);
    slen = strlen(cstr[0]);
    if ((cstr[0])[0] != '0')
        for (i = 1; i < numsSize; ++i) {
            strcat(&ch[slen], cstr[i]);
            slen += strlen(cstr[i]);
        }
bahur:
    if (cstr) free(cstr);
    return ch;
}
















































