int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

typedef struct {} MyCalendarTwo;
MyCalendarTwo*mc2;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair *pushbackP(pair *array, int *size, pair value) {
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

vecp pp;

MyCalendarTwo*myCalendarTwoCreate() {
    pp = newVecP();
    return mc2;
}
bool myCalendarTwoBook(MyCalendarTwo*ooo, int start, int end){
    vecp ker=newVecP();
    for(int i=0; i<pp.sz; i++){
        int x = max(start, pp.ptr[i].first );
        int y = min(end  , pp.ptr[i].second);
        if(x<y)
            ker.ptr = pushbackP(ker.ptr, &ker.sz, newPair(x,y));
    }
    qsort(ker.ptr, ker.sz, sizeof(pair), cmpP);
    for(int i=1; i<ker.sz; i++){
        if(ker.ptr[i-1].second > ker.ptr[i].first)
            return 0;
    }
    pp.ptr = pushbackP(pp.ptr, &pp.sz, newPair(start,end));
    return 1;
}
void myCalendarTwoFree(MyCalendarTwo*ooo){
    pp.sz=0;
    mc2=NULL;
}































