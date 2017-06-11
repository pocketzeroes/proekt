typedef struct pair{
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
pair *pushback(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////
vec a;
int x,y;

typedef struct {
}StringIterator;
StringIterator*ptr;

StringIterator* stringIteratorCreate(char*s){
  a.sz=0;
  char c,i;
  int now;
  now=0;
  for (i=0; s[i]; i++){
    if ((s[i]>='0')&&(s[i]<='9')){
      now*=10;
      now+=s[i]-'0';
    }
    else{
      if (now>0){
        a.ptr = pushback(a.ptr, &a.sz ,newPair(c,now));
      }
      c=s[i];
      now=0;
    }
  }
  if (now>0)
    a.ptr = pushback(a.ptr, &a.sz ,newPair(c,now));
  x=0;y=0;
  return ptr;
}
char stringIteratorNext(StringIterator* obj) {
  if (x>=a.sz) return ' ';
  else
  {
    char c;
    c=a.ptr[x].first;
    y++;
    if (y==a.ptr[x].second)
    {
      x++;y=0;
    }
    return c;
  }
}
bool stringIteratorHasNext(StringIterator* obj) {
  return x<a.sz;  
}
void stringIteratorFree(StringIterator* obj) {
    a.sz=0;
    x=y=0;
}























































