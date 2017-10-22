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
pair*pushback(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVec(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

///////
typedef struct {
}RangeModule;
RangeModule*ptr;
vecp a;

RangeModule*
     rangeModuleCreate(){
  a = newVec();
  return ptr;
}
void rangeModuleAddRange   (RangeModule*obj, int left, int right){
  a.ptr = pushback(a.ptr, &a.sz, newPair(left,right));
}
bool rangeModuleQueryRange (RangeModule*obj, int left, int right){
  if(a.sz == 0) 
    return false;
  int i, j, now;
  vecp d[2];
  d[0] = newVec();
  d[0].ptr = pushback(d[0].ptr, &d[0].sz, newPair(left, right));
  now = 0;
  for(i=a.sz-1; i>=0; i--){
    if (d[now].sz == 0) 
      return true;
    d[1-now].sz = 0;
    if(a.ptr[i].first>0){
      for(j=0; j<d[now].sz; j++){
        if ((a.ptr[i].first>=d[now].ptr[j].second)||(d[now].ptr[j].first>=a.ptr[i].second))
          d[1-now].ptr = pushback(d[1-now].ptr, &d[1-now].sz, d[now].ptr[j]);
        else{
          if((a.ptr[i].first>d[now].ptr[j].first)&&(a.ptr[i].second<d[now].ptr[j].second)){
            d[1-now].ptr = pushback(d[1-now].ptr, &d[1-now].sz, newPair(d[now].ptr[j].first, a.ptr[i].first));
            d[1-now].ptr = pushback(d[1-now].ptr, &d[1-now].sz, newPair(a.ptr[i].second, d[now].ptr[j].second));
          }
          else{
            if(a.ptr[i].second<d[now].ptr[j].second){
              if (d[now].ptr[j].second>a.ptr[i].second)
                d[1-now].ptr = pushback(d[1-now].ptr, &d[1-now].sz, newPair(a.ptr[i].second, d[now].ptr[j].second));
            }
            else{
              if(a.ptr[i].first>d[now].ptr[j].first)
                d[1-now].ptr = pushback(d[1-now].ptr, &d[1-now].sz, newPair(d[now].ptr[j].first, a.ptr[i].first));
            }
          }
        }
      }
    }
    else{
      for (j=0;j<d[now].sz;j++){
        if ((-a.ptr[i].first>=d[now].ptr[j].second)||(d[now].ptr[j].first>=-a.ptr[i].second)){
          d[1-now].ptr = pushback(d[1-now].ptr, &d[1-now].sz, d[now].ptr[j]);
          continue;
        }
        return false;
      }
    }
    now = 1-now;
  }
  if(d[now].sz==0) 
    return true;
  return false;
}
void rangeModuleRemoveRange(RangeModule*obj, int left, int right){
  a.ptr = pushback(a.ptr, &a.sz, newPair(-left,-right));
}
void rangeModuleFree       (RangeModule*obj){
  ptr=NULL;  
}











