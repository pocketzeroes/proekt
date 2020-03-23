#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
#define pb(zpv, zvv) zpv.ptr = pushbacki(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushbacki(int *array, int *size, int value){
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}veci;
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpPii(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
int unique(pair*a, int len){
	int i, j;
	for(i=j=0; i<len; i++)
		if(cmpPii(&a[i], &a[j])!=0)
      a[++j] = a[i];
	return j+1;
}

typedef struct{
  ll first, second;
}pll;
typedef struct{
  pll first;
  ll  second;
}circ;
circ*cv;
int gx;
veci*child;
pair*sols;

double yat(int c, int bot){//puts(__FUNCTION__);
  double r = cv[c].second;
  double dx = cv[c].first.first - gx;
  double dy = sqrt(r*r-dx*dx);
  double rv;
  if(bot)
    rv = cv[c].first.second + dy;
  else
    rv = cv[c].first.second - dy;
  return rv;
}
#if 1// set of pairs
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpP(pair a, pair b){
  double ya = yat(a.first, a.second);
  double yb = yat(b.first, b.second);
  if(ya != yb)
    return(ya < yb)?-1:1;
  return(a.second < b.second)?-1:1;
}

typedef struct AVLTreeNode{
    struct AVLTreeNode*left;
    struct AVLTreeNode*right;
    pair value;
    int count;
    int height;
}AVLTreeNode;
AVLTreeNode newAVLTreeNode(pair val){
    AVLTreeNode rez;
    rez.value  = val;
    rez.count  = 1;
    rez.height = 1;
    rez.left   = NULL;
    rez.right  = NULL;
    return rez;
}
AVLTreeNode*mkAVLTreeNode(pair val){
    AVLTreeNode*rez=calloc(1, sizeof(AVLTreeNode));
    rez->value  = val;
    rez->count  = 1;
    rez->height = 1;
    rez->left   = NULL;
    rez->right  = NULL;
    return rez;
}
typedef AVLTreeNode* AVLTreeNodep;
typedef AVLTreeNodep* AVLTreeNodepp;
void swap(AVLTreeNodepp*nums, int i, int j) {
   AVLTreeNodepp t = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(AVLTreeNodepp*nums, int start, int end){
    while( start < end){
        swap(nums, start, end);
        start++;
        end  --;
    }
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
AVLTreeNodep*pushback(AVLTreeNodep*array, int *size, AVLTreeNodep value){
  AVLTreeNodep*output = resizeArray(array, AVLTreeNodep, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	AVLTreeNodep*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
AVLTreeNodepp*pushback_p(AVLTreeNodepp*array, int *size, AVLTreeNodepp value){
  AVLTreeNodepp*output = resizeArray(array, AVLTreeNodepp, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	AVLTreeNodepp*ptr;
	int sz;
}vec_p;
vec_p newVec_p(){
	vec_p rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void updateValues(AVLTreeNode*tn){
    tn->count  = (tn->left != NULL ? tn->left->count : 0) + (tn->right != NULL ? tn->right->count : 0) + 1;
    tn->height = fmax(tn->left != NULL ? tn->left->height : 0, tn->right != NULL ? tn->right->height : 0) + 1;
}
int balanceFactor(AVLTreeNode*tn){
    return(tn->left != NULL ? tn->left->height : 0) - (tn->right != NULL ? tn->right->height: 0);
}
AVLTreeNode*left_rotate(AVLTreeNode*tn){
    AVLTreeNode*R = tn->right;
    tn->right = tn->right->left;
    R->left = tn;
    updateValues(tn);
    updateValues(R);
    return R;
}
AVLTreeNode*right_rotate(AVLTreeNode*tn){
    AVLTreeNode*L = tn->left;
    tn->left = tn->left->right;
    L->right = tn;
    updateValues(tn);
    updateValues(L);
    return L;
}
typedef struct AVLTree{
    int        _size;
    AVLTreeNode*root;
}AVLTree;
AVLTree newAVLTree(){
    AVLTree rez;
    rez.root  = NULL;
    rez._size = 0;
    return rez;
}
void clear(AVLTree*t){
    vec stack = newVec();
    if(t->root != NULL)
        stack.ptr = pushback(stack.ptr, &stack.sz, t->root);
    while(stack.sz>0){
        AVLTreeNode*node = stack.ptr[stack.sz-1];
        stack.sz--;
        if(node->left != NULL)
            stack.ptr = pushback(stack.ptr, &stack.sz, node->left);
        if(node->right != NULL)
            stack.ptr = pushback(stack.ptr, &stack.sz, node->right);
        t->_size--;
        free(node);
    }
    t->root = NULL;
}
void balance(AVLTree*t, vec_p path){
    reverse(path.ptr, 0, path.sz-1);
    for(int z=0;z<path.sz;z++){AVLTreeNodepp indirect = path.ptr[z];
        updateValues(*indirect);
        if(balanceFactor(*indirect) >= 2 && balanceFactor((*indirect)->left) >= 1)
            *indirect = right_rotate(*indirect);
        else if(balanceFactor(*indirect) >= 2){
            (*indirect)->left = left_rotate((*indirect)->left);
            *indirect = right_rotate(*indirect);
        }
        else if(balanceFactor(*indirect) <= -2 && balanceFactor((*indirect)->right) <= -1)
            *indirect = left_rotate(*indirect);
        else if(balanceFactor(*indirect) <= -2){
            (*indirect)->right = right_rotate((*indirect)->right);
            *indirect = left_rotate(*indirect);
        }
    }
}
void insert(AVLTree*t, pair value){
    AVLTreeNode**indirect = &(t->root);
    vec_p path = newVec_p();
    while(*indirect != NULL){
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
        if(cmpP((*indirect)->value, value)>0)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }
   *indirect = mkAVLTreeNode(value);
    path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    balance(t, path);
    t->_size++;
}
void erase(AVLTree*t, pair value){
    AVLTreeNode**indirect = &(t->root);
    vec_p path = newVec_p();
    while(*indirect != NULL &&cmpP((*indirect)->value, value)!=0){
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
        if(cmpP((*indirect)->value, value)>0)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }
    if(*indirect == NULL)
        return;
    else
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    size_t index = path.sz;
    if((*indirect)->left == NULL && (*indirect)->right == NULL){
        free(*indirect);
        *indirect = NULL;
        path.sz--;
    }
    else if((*indirect)->right == NULL){
        AVLTreeNode*toRemove = *indirect;
        (*indirect) = (*indirect)->left;
        free(toRemove);
        path.sz--;
    }
    else{
        AVLTreeNode**successor = &((*indirect)->right);
        while ((*successor)->left != NULL){
            path.ptr = pushback_p(path.ptr, &path.sz, successor);
            successor = &((*successor)->left);
        }
        if (*successor == (*indirect)->right){
            (*successor)->left = (*indirect)->left;
            AVLTreeNode*toRemove = *indirect;
            *indirect = *successor;
            free(toRemove);
        }
        else{
            AVLTreeNode*tmp = *path.ptr[path.sz-1], *suc = *successor;
            tmp->left = (*successor)->right;
            suc->left = (*indirect)->left;
            suc->right = (*indirect)->right;
            free(*indirect);
            *indirect = suc;
            path.ptr[index] = &(suc->right);
        }
    }
    balance(t, path);
    t->_size--;
}
bool empty(AVLTree*t){
    return t->_size == 0;
}
int size(AVLTree*t){
    return t->_size;
}
int find(AVLTree*t, pair value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while (direct != NULL && cmpP(direct->value, value)!=0){
        if(cmpP(direct->value, value)>0)
            direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    if (direct == NULL)
        return -1;
    else
        return idx + (direct->left ? direct->left->count : 0);
}
int upper_bound(AVLTree*t, pair value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while(direct != NULL){
        if(cmpP(direct->value, value)>0)
           direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    return idx;
}
int lower_bound(AVLTree*t, pair value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while(direct != NULL){
        if(cmpP(direct->value, value)>=0)
           direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    return idx;
}
pair operatorAt(AVLTree*t, size_t idx){
    AVLTreeNode*cur = t->root;
    int left = cur->left != NULL ? cur->left->count : 0;
    while(left != idx){
        if(left < idx){
            idx -= left + 1;
            cur = cur->right;
            left = cur->left != NULL ? cur->left->count : 0;
        }
        else{
            cur = cur->left;
            left = cur->left != NULL ? cur->left->count : 0;
        }
    }
    return cur->value;
}
#endif
///////////////////////////

int incirc(int a, int b){//puts(__FUNCTION__);
  ll dx = cv[a].first.first  - cv[b].first.first;
  ll dy = cv[a].first.second - cv[b].first.second;
  return dx * dx + dy * dy <= cv[b].second * cv[b].second;
}
pair solve(int i, int n){//puts(__FUNCTION__);
  pair r = newpair(0, 0);
  r.first = 1;
  for(int z=0;z<child[i].sz;z++){int c = child[i].ptr[z];
    pair p = solve(c, n);
    if(c < n){
      r.first  += p.second;
      r.second += fmax(p.first, p.second);
    }
    else{
      r.first  += p.first - 1;
      r.second += p.second;
    }
  }
  sols[i] = r;
  return r;
}
int main(){//puts(__FUNCTION__);
  int n, m;
  scanf("%d %d", &n, &m);
  cv = calloc(n+m, sizeof(circ));
  int ssz=(n+m)*2;
  int s=0;
  pair*sweep = calloc(ssz, sizeof(pair));
//puts("for1");
  for(int i=0; i<n+m; i++){
    scanf("%lld %lld %lld", &cv[i].first.first, &cv[i].first.second, &cv[i].second);
    sweep[s++] = newpair(cv[i].first.first-cv[i].second, i);
    sweep[s++] = newpair(cv[i].first.first+cv[i].second, i);
  }
//puts("for1done");
  qsort(sweep, ssz, sizeof(pair), cmpPii);
  ssz = unique(sweep, ssz);
  AVLTree oc = newAVLTree(); // set<pair, cmpP>
  int psz=n+m;
  int parent[psz]; clr(parent);
//puts("for2");
  for(int z=0; z<ssz; z++){pair v = sweep[z];
    int x = v.first;
    int i = v.second;
    gx = x;
    if(x < cv[i].first.first){
      int p = lower_bound(&oc, newpair(i,0));
      pair pp;
      int  p1st;
      if(p!=size(&oc)){
        pp = operatorAt(&oc, p);
        p1st = pp.first;
      }
      if(p == size(&oc))
        parent[i] = m+n;
      else if(incirc(i, p1st))
        parent[i] = p1st;
      else
        parent[i] = parent[p1st];
      insert(&oc, newpair(i, 0));
      insert(&oc, newpair(i, 1));
    }
    else{
      erase(&oc, newpair(i, 0));
      erase(&oc, newpair(i, 1));
    }
  }
//puts("for2done");
  child = calloc(n+m+1, sizeof(veci));
//puts("for3");
  for(int i=0; i<psz; i++)
    pb(child[parent[i]], i);
//puts("for3done");
  sols=calloc(n+m+1, sizeof(pair));
  solve(m+n, n);
//puts("for4");
  for(int i=n; i<n+m; i++)
    printf("%d\n",(int)fmax(sols[i].first, sols[i].second));
//puts("for4done");
  return 0;
}
