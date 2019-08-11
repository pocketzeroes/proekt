typedef struct {
}MajorityChecker;
MajorityChecker*gptr;
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


int N;
int A[20202];
vec B;
int C[20202];
int S[20202][202];

MajorityChecker*majorityCheckerCreate(int*arr, int arrSz){
  int i,x;
  memset(C,0,sizeof(C));
  memset(S,0,sizeof(S));
  N=arrSz;
  for(i=0;i<(N);i++) {
   A[i]=arr[i];
   C[A[i]]++;
  }
  B.sz=0;
  for(i=0;i<(20002);i++)
    if(C[i]>100)
      B.ptr=pushback(B.ptr, &B.sz, i);
  memset(C,0,sizeof(C));
  for(i=0;i<(B.sz);i++){
   for(x=0;x<(N);x++) {
    S[x+1][i]=S[x][i];
    if(A[x]==B.ptr[i])
      S[x+1][i]++;
   }
  }
  return gptr;
}
int majorityCheckerQuery(MajorityChecker* obj, int left, int right, int threshold) {
  int ret=-1;
  if(threshold>100) {
   int i;
   for(i=0;i<(B.sz);i++) {
    if(S[right+1][i]-S[left][i]>=threshold)
      ret=B.ptr[i];
   }
  }
  else {
   int i;
   for(i=left;i<=right;i++) {
    C[A[i]]++;
    if(C[A[i]]>=threshold)
      ret=A[i];
   }
   for(i=left;i<=right;i++)
     C[A[i]]--;
  }
  return ret;
}
void majorityCheckerFree(MajorityChecker* obj) {
  ;
}
