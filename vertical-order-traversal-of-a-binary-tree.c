
typedef struct TreeNode TreeNode;

typedef struct{
    int x, y, val;
}point;
point newPoint(int a, int b, int c){
    point rez;
    rez.x    =a;
    rez.y    =b;
    rez.val  =c;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
point*pushbackPt(point*array, int *size, point value){
    point*output = resizeArray(array, point, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	point*ptr;
	int sz;
}vecpt;
vecpt newVecPt(){
	vecpt rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
vecpt ps;

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int**pushback2d(int**array, int*size, int* value){
  int* *output = resizeArray(array, int*, *size + 1);
  output[(*size)++] = value;
  return output;
}
/////////////////////

void dfs(TreeNode*v, int x, int y){
    ps.ptr = pushbackPt(ps.ptr, &ps.sz, newPoint(x, y, v->val));
    if(v->left!=NULL)
        dfs(v->left,x-1,y-1);
    if(v->right!=NULL)
        dfs(v->right,x+1,y-1);
}
int cmpP(const void*pa, const void*pb){ 
    point*a=(point*)pa;
    point*b=(point*)pb;
    if(a->x == b->x && a->y == b->y)
        return (a->val < b->val)?-1:1;
    else if(a->x == b->x)
        return (a->y > b->y)?-1:1;
    else
        return (a->x < b->x)?-1:1;
}
int**ans;
int  ansSz;
int*sizes;

int**verticalTraversal(TreeNode*root, int**outcols, int*rsz){
    ansSz=0;
    sizes = calloc(1000, sizeof(int));
    ps.sz=0;
    dfs(root, 0, 0);
    qsort(ps.ptr, ps.sz, sizeof(point), cmpP);
    int pre = ps.ptr[0].x;

    vec crt = newVec();
    for(int i=0; i<ps.sz; i++){
        if(ps.ptr[i].x==pre){
            crt.ptr = pushback(crt.ptr, &crt.sz, ps.ptr[i].val);
        }
        else{
            sizes[ansSz] = crt.sz;
            int*tt = calloc(crt.sz, sizeof(int));
            memcpy(tt, crt.ptr, crt.sz*sizeof(int));
            ans = pushback2d(ans, &ansSz, tt);

            crt.sz=0;
            crt.ptr = pushback(crt.ptr, &crt.sz, ps.ptr[i].val);
            pre = ps.ptr[i].x;
        }
    }
    sizes[ansSz] = crt.sz;
    int*tt = calloc(crt.sz, sizeof(int));
    memcpy(tt, crt.ptr, crt.sz*sizeof(int));
    ans = pushback2d(ans, &ansSz, tt);

 *outcols = sizes;
 *rsz=   ansSz;
  return ans;
}


