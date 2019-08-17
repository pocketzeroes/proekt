#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void err() {
  puts("syntax error");
  exit(0);
}
typedef struct{
  int x;
  int ya;
  int yb;
  int type;
}event;
event newEvent(int a, int b, int c, int d){
  return(event){a, b, c, d};
}
int cmpE(const void*pa, const void*pb){
  event*this =(event*)pa;
  event*other=(event*)pb;
  if(this->x != other->x)
    return (this->x < other->x)?-1:1;
  return (this->type > other->type)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
event*pushbackE(event *array, int *size, event value){
  event *output = resizeArray(array, event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  event*ptr;
  int sz;
}vece;

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  return(pair){a, b};
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
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
int qcmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

#if 1// set
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
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
int test_set_main(){
    AVLTree tree = newAVLTree();
    for(int i=0; i <11; i++){
        pair x = newPair(rand(), rand());
        insert(&tree, x);
    }
    for(int i=0; i < size(&tree); i++){
        pair pi = operatorAt(&tree, i);
        printf("%d %d\n", pi.first, pi.second);
    }
    clear(&tree);
    printf("%d\n", size(&tree));
    return 0;
}

#endif




typedef struct{
  int first;
  int second;
  int third;
}trip;
trip newTrip(int a, int b, int c){
  return(trip){a,b,c};
}
int cmpT(const void*pa, const void*pb){
  trip*a = (trip*)pa;
  trip*b = (trip*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  if(a->third  != b->third )return(a->third  < b->third )?-1:1;
  return 0;
}

vece e;

void make_rect(int xa, int ya, int xb, int yb) {
  e.ptr=pushbackE(e.ptr, &e.sz ,newEvent( xa,ya,yb, 1 ));
  e.ptr=pushbackE(e.ptr, &e.sz ,newEvent( xb,ya,yb,-1 ));
}

enum{ N = 200010};
int n;
trip p[N];
int ans[N];
int x[N], y[N];
void make(int i, int j) {
  ans[i] = j - n;
  if (x[i] == x[j] || y[i] == y[j])
    make_rect(x[i], y[i], x[j], y[j]);
  else{
    make_rect(x[i], y[i], x[j] - 1, y[i]);
    make_rect(x[j], y[i], x[j], y[j] - 1);
    make_rect(x[i] + 1, y[j], x[j], y[j]);
    make_rect(x[i], y[i] + 1, x[i], y[j]);
  }
}
enum{ MAX = 4000010};
int add[MAX], mx[MAX];



void push(int x) {
  add[x + x] += add[x];
  add[x + x + 1] += add[x];
  add[x] = 0;
}
void pull(int x) {
  mx[x] = fmax(mx[x + x] + add[x + x], mx[x + x + 1] + add[x + x + 1]);
}
int modify(int x, int l, int r, int ll, int rr, int v) {
  if (ll <= l && r <= rr) {
    int res = mx[x] + add[x];
    add[x] += v;
    return res;
  }
  push(x);
  int y = (l + r) >> 1;
  int res = 0;
  if (ll <= y)
    res = fmax(res, modify(x + x, l, y, ll, rr, v));
  if (rr > y)
    res = fmax(res, modify(x + x + 1, y + 1, r, ll, rr, v));
  pull(x);
  return res;
}
int main(){
  scanf("%d", &n);
  for(int i = 0; i<n + n; i++){
    scanf("%d %d", x + i, y + i);
    p[i] = newTrip(x[i], y[i], i);
  }
  qsort(p, n+n, sizeof(trip), cmpT);
  AVLTree s = newAVLTree();//of pair
  for(int id = 0; id<n + n; id++){
    int i = p[id].third;
    if(i<n)
      insert(&s, newPair(y[i], i));
    else{
      int idx = lower_bound(&s, newPair(y[i]+1, -1));
      if(idx == 0)
        err();
      pair it = operatorAt(&s, idx-1);
      make(it.second, i);
      erase(&s, it);
    }
  }
  vecp ys=newVecP();
  for (int i=0; i<e.sz; i++) {
    ys.ptr=pushbackP(ys.ptr, &ys.sz ,newPair(e.ptr[i].ya,      i));
    ys.ptr=pushbackP(ys.ptr, &ys.sz ,newPair(e.ptr[i].yb + 1, ~i));
  }
  qsort(ys.ptr, ys.sz, sizeof(pair), qcmpP);
  int t = 0;
  for(int i = 0; i<ys.sz; i++) {
    if(i == 0 || ys.ptr[i].first != ys.ptr[i - 1].first)
      t++;
    int id = ys.ptr[i].second;
    if(id >= 0)
      e.ptr[id].ya = t;
    else
      e.ptr[~id].yb = t - 1;
  }
  qsort(e.ptr, e.sz, sizeof(event), cmpE);
  for(int i = 0; i<e.sz; i++){
    int z = modify(1, 1, t, e.ptr[i].ya, e.ptr[i].yb, e.ptr[i].type);
    if(e.ptr[i].type == 1 && z > 0)
      err();
  }
  for(int i = 0; i<n; i++)
    printf("%d\n", ans[i] + 1);
  return 0;
}
