#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

char**pushback(char**array, int *size, char*value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}

char** readBinaryWatch(int num, int* returnSize){
    char**result=NULL;
    for (int h = 0; h < 12; ++h) {
        for (int m = 0; m < 60; ++m) {
            if (__builtin_popcount(h) + __builtin_popcount(m) == num) {
                int hour   = h;
                int minute = m;
                char*time;
                asprintf(&time,"%d:%02d", hour, minute);
                result=pushback(result, returnSize, time);
            }
        }
    }
    return result;
}
