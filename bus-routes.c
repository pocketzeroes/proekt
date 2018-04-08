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
/////
vec a   [300000 ];
int ind [1100000];
int used[300000 ];

int numBusesToDestination(int**r, int rSz, int*rszs, int s, int t){
  int i, j, k, x, y, z, n;
  vec q  = newVec();
  vec aa = newVec();
  for(i=0; i<300000; i++)
    a[i].sz=0;
  memset(ind, -1, sizeof(ind));
  n=0;
  for (i=0; i<rSz; i++){
    aa.sz=0;
    for (j=0; j<rszs[i]; j++){
      if (ind[r[i][j]]==-1){
        ind[r[i][j]]=n;
        n++;
      }
      aa.ptr = pushback(aa.ptr, &aa.sz, ind[r[i][j]]);
    }
    for (j=0; j<aa.sz; j++){
      a[aa.ptr[j]].ptr = pushback(a[aa.ptr[j]].ptr, &a[aa.ptr[j]].sz, n);
      a[n].ptr = pushback(a[n].ptr, &a[n].sz, aa.ptr[j]);
    }
    n++;
  }
  if (s==t)
    return 0;
  if ((ind[s]==-1)||(ind[t]==-1))
    return -1;
  memset(used, -1, sizeof(used));
  q.sz=0;
  q.ptr = pushback(q.ptr, &q.sz, ind[s]);
  used[ind[s]]=0;
  for(i=0; i<q.sz; i++){
    x = q.ptr[i];
    z = used[x];
    for(j=0; j<a[x].sz; j++){
      y = a[x].ptr[j];
      if(used[y]==-1){
        used[y]=z+1;
        q.ptr = pushback(q.ptr, &q.sz, y);
      }
    }
  }
  if(used[ind[t]]==-1) 
    return -1;
  return used[ind[t]]/2;
}
