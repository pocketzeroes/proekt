int max(int a,int b){return a>b?a:b;}
typedef struct Interval Interval;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
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

Interval newInterval(int a, int b){
    Interval rez;
    rez.start =a;
    rez.end   =b;
    return rez;
}
Interval*pushbackI(Interval *array, int *size, Interval value) {
    Interval *output = resizeArray(array, Interval, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	Interval*ptr;
	int sz;
}veci;
veci newVecI() {
	veci rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ MOD =(int) 1e9+7};

int d[100];
Interval*employeeFreeTime(Interval**a, int aSz, int*a0sz, int*rsz){
  veci ans = newVecI();
  memset(d, 0, sizeof(d));
  int i, j, k, now, n, min, b1;
  n = aSz;
  ans.sz=0;
  now = -1;
  while(1){
    b1 = 1;
    while(b1==1){
      b1=0;
      for(i=0;i<n;i++){
        if((d[i]<a0sz[i]) && (a[i][d[i]].start<=now)){
          if(a[i][d[i]].end>now)
            now = a[i][d[i]].end;
          d[i]++;
          b1=1;
        }
      }
    }
    b1=0;
    for(i=0;i<n;i++)
      if(d[i]!=a0sz[i]){
        b1=1;break;
      }
    if (b1==0)
      break;
    min=2000000000;
    for (i=0;i<n;i++)
      if ((d[i]<a0sz[i]) && (a[i][d[i]].start<min)) 
        min=a[i][d[i]].start;
    Interval inv;
    inv.start=now;
    inv.end = min;
    if (now!=-1)
      ans.ptr = pushbackI(ans.ptr, &ans.sz, inv);
    now=inv.end;
  }
 *rsz=   ans.sz;
  return ans.ptr;
}
