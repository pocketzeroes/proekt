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
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}


//////////////////////////
int*eventualSafeNodes(int**graph, int graphSz, int*graphSzs, int*rsz){
    vec ans = newVec();
    vec2d g = newVec2d();
    ans.sz=0;
    g.sz=0;
    int n=graphSz, m,i,j,q[10005],he,ta,in[10005];
    bool b[10005];
    for(i=0; i<n; i++)
        g.ptr = pushback2d(g.ptr, &g.sz, ans);
    for(i=0; i<n; i++)
        for(m=graphSzs[i],j=0; j<m; j++)
            g.ptr[graph[i][j]].ptr = pushback(g.ptr[graph[i][j]].ptr, &g.ptr[graph[i][j]].sz, i);
    memset(b, 0, sizeof(b));
    he=ta=0;
    for(i=0; i<n; i++){
        in[i]=graphSzs[i];
        if(graphSzs[i]==0)
            b[q[ta++]=i]=1;
    }
    while(he!=ta){
        i=q[he++];
        m=g.ptr[i].sz;
        for(j=0; j<m; j++){
            in[g.ptr[i].ptr[j]]--;
            if(!in[g.ptr[i].ptr[j]])
                b[q[ta++]=g.ptr[i].ptr[j]]=1;
        }
    }
    for(i=0; i<n; i++)
        if(b[i])
            ans.ptr = pushback(ans.ptr, &ans.sz, i);
   *rsz=   ans.sz;
    return ans.ptr;
}
