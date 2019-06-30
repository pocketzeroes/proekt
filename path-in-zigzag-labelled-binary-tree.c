#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}

int*pathInZigZagTree(int label, int*rsz){
    vec path=newVec();
    path.ptr = pushback(path.ptr, &path.sz, label);
    int row = 31 - __builtin_clz(label);
    while (row > 0) {
        int position;
        if (row % 2 == 0)
            position = label - (1 << row);
        else
            position = 2 * (1 << row) - 1 - label;
        position /= 2;
        row--;
        if (row % 2 == 0)
            label = (1 << row) + position;
        else
            label = 2 * (1 << row) - 1 - position;
        path.ptr = pushback(path.ptr, &path.sz, label);
    }
    reverse(path.ptr, 0, path.sz-1);
    *rsz=  path.sz;
    return path.ptr;
}
