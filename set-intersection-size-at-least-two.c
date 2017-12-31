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

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
int cmp(const void*pa, const void*pb){
    int**v1p=(int**)pa;
    int**v2p=(int**)pb;
    int*v1= *v1p;
    int*v2= *v2p;
    return (v1[0]<v2[0] || v1[0]==v2[0] && v1[1]>v2[1])?-1:1;
}
int intersectionSizeTwo(int**intervals, int intervalsSz, int intervals0sz){
    qsort(intervals, intervalsSz,sizeof(int*), cmp);
    vecp arr = newVecP();
    int count=0,n=0;
    for(int i=0; i<intervalsSz; i++){
        while(arr.sz && arr.ptr[n-1].second > intervals[i][1]){
            arr.sz--;
            n--;
        }
        arr.ptr = pushbackP(arr.ptr, &arr.sz, newPair(intervals[i][0], intervals[i][1]));
        n++;
    }
    int l1=-2, l2=-1;
    for(int i=0; i<n; i++){
        if(l2<arr.ptr[i].first){
            l1 = arr.ptr[i].second-1;
            l2 = arr.ptr[i].second;
            count+=2;
            continue;
        }
        if(l1< arr.ptr[i].first){
            l1=arr.ptr[i].second;
            if(l1==l2)
                l1--;
            if(l1>l2)
                swap(l1, l2);
            count++;
            continue;
        }
    }
    return count;
}
