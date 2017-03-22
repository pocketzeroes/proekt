#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int*countBits(int num,int*rsz){
    int*res=NULL;
    for (int i = 0; i <= num; ++i)
        res=pushback(res,rsz,__builtin_popcount(i));
    return res;
}
