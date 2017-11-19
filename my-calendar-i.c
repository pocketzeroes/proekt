typedef struct {}MyCalendar;
MyCalendar*gmc;
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

vecp pp;

MyCalendar*myCalendarCreate(){
    pp = newVecP();
    return gmc;    
}
bool myCalendarBook(MyCalendar*m1c, int start, int end){
    for(int i=0; i<pp.sz; i++){
        if(!(pp.ptr[i].second<=start || end<=pp.ptr[i].first))
            return 0;
    }
    pp.ptr = pushbackP(pp.ptr, &pp.sz, newPair(start,end));
    return 1;
}
void myCalendarFree(MyCalendar*m1c){
    pp.sz=0;
    gmc=NULL;
}




































