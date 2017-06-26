int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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

////
typedef int* intp;
int cmp(const void*pa, const void*pb){
    intp*a=(intp*)pa;
    intp*b=(intp*)pb;
    int*c1 = *a;
    int*c2 = *b;
    return (c1[1] < c2[1])?-1:1;
}

int scheduleCourse(int**courses, int cRowSz, int cColSz){
    qsort(courses, cRowSz, sizeof(intp), cmp);
    vec best=newVec();
    best.ptr = pushback(best.ptr, &best.sz, 0);
    for(int i=0;i<cRowSz;i++){int*course = courses[i];
        int t = course[0], d = course[1];
        if (t > d) 
            continue;
        int m = best.sz;
        if (best.ptr[m-1]+t<=d) 
            best.ptr = pushback(best.ptr, &best.sz ,best.ptr[m-1]+t);
        for (int i = m-1; i>0; --i){
            if (best.ptr[i-1] + t <= d) {
                best.ptr[i] = min(best.ptr[i], best.ptr[i-1] + t);
            }
        }
    }
    return best.sz - 1;
}



