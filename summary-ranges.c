#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

char**pushback(char**array, int *size, char*value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}

char**summaryRanges(int*nums,int numsSz,int*rsz) {
    char**ranges=NULL;
   *rsz=0;
    if (numsSz==0) 
        return ranges;
    int start = nums[0], end = nums[0];
    for (int i = 1; i <= numsSz; ++i) {
        if (i < numsSz && nums[i] == end + 1) {
            end = nums[i];
        }
        else  {
            char* range;
            asprintf(&range,"%d",start);
            char*line;
            if (start != end) {
                asprintf(&line,"%s->%d", range, end);
                free(range);
                range=NULL;
                range=strdup(line);
            }
            ranges=pushback(ranges,rsz,range);
            if (i < numsSz) {
                start = end = nums[i];
            }
        }
    }
    return ranges;
}
