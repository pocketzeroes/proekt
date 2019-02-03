int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct Interval Interval;

Interval newInterval(int a, int b){
    Interval rez;
    rez.start=a;
    rez.end  =b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Interval*pushbackI(Interval*array, int *size, Interval value){
    Interval*output = resizeArray(array, Interval, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	Interval*ptr;
	int sz;
}veci;
veci newVecI(){
	veci rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////////

int cmp(const void*pa, const void*pb){
    Interval*x=(Interval*)pa;
    Interval*y=(Interval*)pb;
    return(x->start < y->start)?-1:1;
}
Interval*intervalIntersection(Interval*A, int Asz, Interval*B, int Bsz, int*rsz){
    qsort(A, Asz, sizeof(Interval), cmp);
    qsort(B, Bsz, sizeof(Interval), cmp);
    veci ans = newVecI();
    int i = 0, j = 0;
    while(i < Asz && j < Bsz){
        int le = max(A[i].start, B[j].start);
        int ri = min(A[i].end  , B[j].end  );
        if(le <= ri)
            ans.ptr = pushbackI(ans.ptr, &ans.sz, newInterval(le, ri));
        if(A[i].end < B[j].end)
            i++;
        else
            j++;
    }
   *rsz =  ans.sz;
    return ans.ptr;
}
