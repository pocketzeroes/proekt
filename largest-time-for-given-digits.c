int cmp(const void * a, const void * b){   return ( *(int*)a - *(int*)b );}
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

char*largestTimeFromDigits(int*A, int Asz){
    qsort(A, Asz, sizeof(int), cmp);
    char*answer = strdup("");
    for(int t=0; t<2400; t++){
        if(t % 100 >= 60)
            continue;
        vec digits = newVec();
        int t_copy = t;
        for(int i=0; i<4; i++){
            digits.ptr = pushback(digits.ptr, &digits.sz, t_copy % 10);
            t_copy /= 10;
        }
        qsort(digits.ptr, digits.sz, sizeof(int), cmp);
        bool eq = true;
        if(Asz==digits.sz){
            for(int z=0; z<Asz; z++)
                if(A[z] != digits.ptr[z]){
                    eq=false;
                    break;
                }
        }
        else{
            eq = false;
        }
        if(eq){
            char str[100];
            sprintf(str, "%02d:%02d", t / 100, t % 100);
            answer = strdup(str);
        }
    }
    return answer;
}
