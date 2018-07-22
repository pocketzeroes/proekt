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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first != b->first )return(a->first  < b->first )?-1:1;
  if(a->second!= b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int lower_boundP(pair*a, int n, pair x){
    int l = 0;
    int h = n;
    while(l < h){
        int mid = (l + h) / 2;
        if(cmpP(&x, &a[mid])<=0)
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}
/////////////////////////
const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};

void amax(int*x, int y){ 
  if(*x < y) 
     *x = y;
}
int robotSim(int*commands, int commandsSz, int**obstacles, int obstaclesSz, int*obstacle0szs){
    vecp P = newVecP();
    for(int i=0, i_len=obstaclesSz; i<i_len; ++i){
        P.ptr = pushbackP(P.ptr, &P.sz, newPair(obstacles[i][0], obstacles[i][1]));
    }
    qsort(P.ptr, P.sz, sizeof(pair), cmpP);
    int curX = 0, curY = 0, curD = 0;
    int ans = 0;
    for(int z=0;z<commandsSz;z++){int e=commands[z];
        if(e == -1)
          curD = (curD + 1) % 4;
        else if(e == -2)
          curD = (curD + 3) % 4;
        else{
          for(int t=0, t_len=e; t<t_len; ++t) {
            int nxtX = curX + dx[curD];
            int nxtY = curY + dy[curD];
            pair key = newPair(nxtX, nxtY);
            int k = lower_boundP(P.ptr, P.sz, key);
            if(k < P.sz && cmpP(&P.ptr[k], &key)==0)
              break;
            else{
              curX = nxtX;
              curY = nxtY;
            }
          }
        }
        amax(&ans, curX*curX + curY*curY);
    }
    return ans;
}
