void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int good[1100];
int used[1100];
int*movesToStamp(char*s, char*t, int*rsz){
  int i,j,k,ls,lt;
  vec q   = newVec();
  vec ans = newVec();
  ls = strlen(s);
  lt = strlen(t);
  memset(good, 0, sizeof(good));
  memset(used, 0, sizeof(used));
  for(i=0; i+ls<=lt; i++){
    for(j=0; j<ls; j++)
      if(s[j] == t[i+j])
        good[i]++;
    if(good[i] == ls){
      q.ptr = pushback(q.ptr, &q.sz, i);
      used[i]=1;
    }
  }
  ans.sz=0;
  for(i=0; i<q.sz; i++){
    ans.ptr = pushback(ans.ptr, &ans.sz, q.ptr[i]);
    for(j=0; j<ls; j++)
      if(t[q.ptr[i]+j]!='?'){
        for(k=0;k+ls<=lt;k++)
          if((used[k]==0)&&(q.ptr[i]+j-k>=0)&&(q.ptr[i]+j-k<ls)){
            if(s[q.ptr[i]+j-k] != t[q.ptr[i]+j]){
              good[k]++;
              if(good[k]==ls){
                q.ptr = pushback(q.ptr, &q.sz, k);
                used[k] = 1;
              }
            }
          }
        t[q.ptr[i]+j] = '?';
      }
  }
  if(ans.sz!=lt-ls+1){
    ans.sz=0;
   *rsz=0;
    return ans.ptr;
  }
  reverse(ans.ptr, 0, ans.sz-1);
 *rsz=ans.sz;
  return ans.ptr;
}
