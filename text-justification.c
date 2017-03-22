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

char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    char**result=NULL;
    int n = wordsSize;
    int sum = 0;
    int num = 0;
    for (int i=0; i<n; i++) {
        sum += strlen(words[i]);
        num++;
        if (sum + num - 1 > maxWidth || i == n - 1) {
            if (sum + num - 1 > maxWidth) {
                sum -= strlen(words[i]);
                num--;
                i--;
            }
            char*line = malloc(1024);memset(line, 0, 1024);
            int num_extra = maxWidth - sum;
            int num_extra_left = num_extra;
            for (int j=0; j<num; j++) {
                strcat(line , words[i-num+j+1]);
                int num_extra_use = 0;
                if (i == n - 1)
                    num_extra_use = 1;
                if (j != num - 1 && i != n - 1)
                    num_extra_use = num_extra_left / (num - j - 1) + (num_extra_left % (num - j - 1) == 0 ? 0 : 1);
                if (j == num - 1 && i == n - 1)
                    num_extra_use = num_extra_left;
                if(num_extra_use>0)
                {
                    char space[num_extra_use+1]; memset(space, ' ' , sizeof(space)); space[num_extra_use]='\0';
                    strcat(line , space);
                }
                num_extra_left -= num_extra_use;
            }
            if(num_extra_left>0)
            {
                char spce[num_extra_left+1]; memset(spce, ' ' , sizeof(spce)); spce[num_extra_left]='\0';
                strcat(line , spce);
            }
            result = pushback(result, returnSize, line);
            sum = 0;
            num = 0;
        }
    }
    return result;
}
