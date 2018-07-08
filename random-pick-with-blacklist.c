int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct {
}Solution;
Solution*gsol;
vecp whiterange;
int range_size;
Solution* solutionCreate(int N, int*blacklist, int blacklistSz){
    whiterange = newVecP();
    qsort(blacklist, blacklistSz, sizeof(int), cmp);
    int white = 0;
    for(int z=0;z<blacklistSz;z++){int black = blacklist[z];
        if(black - white == 1)
            whiterange.ptr = pushbackP(whiterange.ptr, &whiterange.sz, newPair(white,white));
        else if(black - white > 1) 
            whiterange.ptr = pushbackP(whiterange.ptr, &whiterange.sz, newPair(white,black-1));
        white = black+1;
    }
    if(white < N)
        whiterange.ptr = pushbackP(whiterange.ptr, &whiterange.sz, newPair(white,N-1));
    range_size = whiterange.sz;
    return gsol;
}
int solutionPick(Solution* obj) {
    int index = rand()%range_size;
    int range_start = whiterange.ptr[index].first;
    int range_end = whiterange.ptr[index].second;
    return (rand()%((range_end - range_start)+1)) + range_start;
}
void solutionFree(Solution* obj) {
    
}
