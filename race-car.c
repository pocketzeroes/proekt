
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

int d[100000][40];

int racecar(int target){
  int i,j,k,ans,x,xx,ac,acc,z;
  vecp q = newVecP();
  q.ptr = pushbackP(q.ptr, &q.sz, newPair(0,0));
  memset(d, -1, sizeof(d));
  d[50000][20]=0;
  for(i=0; i<q.sz; i++){
    x  = q.ptr[i].first;
    ac = q.ptr[i].second;
    z  = d[x+50000][ac+20];
    {
      if(ac>=0)
        xx=x+(1<<ac);
      else
        xx=x-(1<<(-(ac+1)));
      if(ac>=0)
        acc=ac+1;
      else
        acc=ac-1;
      if((xx>=-50000)&&(xx<50000)){
        if(d[xx+50000][acc+20]==-1){
          d[xx+50000][acc+20]=z+1;
          q.ptr = pushbackP(q.ptr, &q.sz, newPair(xx,acc));
          if(xx==target){
            ans=z+1;
            break;
          }
        }
      }
    }
    {
      xx=x;
      if(ac>=0)
        acc=-1;
      else
        acc=0;
      if((xx>=-50000)&&(xx<50000)){
        if(d[xx+50000][acc+20]==-1){
          d[xx+50000][acc+20]=z+1;
          q.ptr = pushbackP(q.ptr, &q.sz, newPair(xx,acc));
          if(xx==target){
            ans = z+1;
            break;
          }
        }
      }
    }
  }
  return ans;
}
