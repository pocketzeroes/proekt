#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int*nextGreaterElements(int*nums,int n,int*rsz){
    int*gtr=NULL;
    for(int i=0; i<n; ++i){
        int j = (i + 1) % n;
        while(j != i && nums[i] >= nums[j])
            j = (j + 1) % n;
        if(j != i) 
            gtr=pushback(gtr,rsz,nums[j]);
        else 
            gtr=pushback(gtr,rsz,-1);
    }
    return gtr;
}
     