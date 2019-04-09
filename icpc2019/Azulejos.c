#pragma GCC optimize "-O3"

#if 1// set
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
    tn->height = max(tn->left != NULL ? tn->left->height : 0, tn->right != NULL ? tn->right->height : 0) + 1;
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

#define forn(i,n) for(int i=0;i<n;i++)
#define pb pushback
#define fi first
#define se second

void iota(int*arr, int sz, int beg){
  for(int i=0; i<sz; i++)
    arr[i] = i;
}
int main(){
  int n;
  scanf("%d", &n);
  int b_h[n]; int b_p[n];
  int f_h[n]; int f_p[n];
  for(int i=0; i<n; i++) scanf("%d", &b_p[i]);
  for(int i=0; i<n; i++) scanf("%d", &b_h[i]);
  for(int i=0; i<n; i++) scanf("%d", &f_p[i]);
  for(int i=0; i<n; i++) scanf("%d", &f_h[i]);
  int b_order[n];int f_order[n];
  iota(b_order, n, 0);
  iota(f_order, n, 0);
int cmpB(const void*pa, const void*pb){
  int*ptra=(int*)pa; int*ptrb=(int*)pb; int i=*ptra; int j=*ptrb;
  return(b_p[i]<b_p[j])?-1:1;
}
int cmpF(const void*pa, const void*pb){
  int*ptra=(int*)pa; int*ptrb=(int*)pb; int i=*ptra; int j=*ptrb;
  return(f_p[i]<f_p[j])?-1:1;
}
  qsort(b_order, n, sizeof(int), cmpB);
  qsort(f_order, n, sizeof(int), cmpF);
  int b_i = 0;
  int f_i = 0;
  AVLTree b_s = newAVLTree();
  AVLTree f_s = newAVLTree();
  int b_ans[n]; int f_ans[n];
  for(int iter=0; iter<n; iter++){
    if(empty(&b_s)){
      while(b_i<n){
        insert(&b_s, newPair(b_h[b_order[b_i]], b_order[b_i]));
        b_i++;
        if(b_i==n||b_p[b_order[b_i-1]]!=b_p[b_order[b_i]])
          break;
      }
    }
    if(empty(&f_s)){
      while(f_i<n){
        insert(&f_s, newPair(f_h[f_order[f_i]], f_order[f_i]));
        f_i++;
        if(f_i==n||f_p[f_order[f_i-1]]!=f_p[f_order[f_i]])
          break;
      }
    }
    if(size(&b_s) < size(&f_s)){
      pair bsBegin = operatorAt(&b_s, 0);
      int i = bsBegin.second;
      erase(&b_s, bsBegin);
      b_ans[iter] = i;
      int it = lower_bound(&f_s, newPair(b_h[i], -1));
      if(it == 0){
        puts("impossible");
        return 0;
      }
      --it;
      pair fit = operatorAt(&f_s, it);
      f_ans[iter] = fit.second;
      erase(&f_s, fit);
    }
    else{
      pair fsBegin = operatorAt(&f_s, 0);
      int i = fsBegin.second;
      erase(&f_s, fsBegin);
      f_ans[iter] = i;
      int it = lower_bound(&b_s, newPair(f_h[i]+1, -1));
      if(it == size(&b_s)){
        puts("impossible");
        return 0;
      }
      pair bit = operatorAt(&b_s, it);
      b_ans[iter] = bit.second;
      erase(&b_s, bit);
    }
  }
  for(int i=0; i<n; i++){
    if(i>0)
      printf(" ");
    printf("%d", b_ans[i]+1);
  }
  puts("");
  for(int i=0; i<n; i++){
    if(i>0)
      printf(" ");
    printf("%d", f_ans[i]+1);
  }
  puts("");
  return 0;
}
