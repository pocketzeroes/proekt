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

char**pushback(char**array, int *size, char* value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}


enum{ inf = 0x3f3f3f3f};

char** findRestaurant(char** list1, int list1sz, char** list2, int list2sz, int* retSz){
  pair best = newPair(inf, inf);
  for (int i = 0; i < list1sz; ++i) {
    for (int j = 0; j < list2sz && i + j <= best.first + best.second; ++j) {
      if(strcmp(list1[i] , list2[j]) == 0){
        best = newPair(i, j);
      }
    }
  }
  char**res=NULL; int resSz=0;
  for (int i = 0; i < list1sz; ++i) {
    for (int j = 0; j < list2sz; ++j) {
      if (i + j == best.first + best.second && strcmp(list1[i] , list2[j])==0 ) {
        res=pushback(res, &resSz ,list1[i]);
      }
    }
  }
 *retSz = resSz;
  return res;
}
