#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
#define pb(zpv, zvv) zpv.ptr = pushbacki(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushbacki(int *array, int *size, int value){
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  int*ptr;
  int sz;
}veci;
veci newVeci(){
  veci rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

#if 1//set
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


typedef struct AVLTreeNode{
    struct AVLTreeNode*left;
    struct AVLTreeNode*right;
    int value;
    int count;
    int height;
}AVLTreeNode;
AVLTreeNode newAVLTreeNode(int val){
    AVLTreeNode rez;
    rez.value  = val;
    rez.count  = 1;
    rez.height = 1;
    rez.left   = NULL;
    rez.right  = NULL;
    return rez;
}
AVLTreeNode*mkAVLTreeNode(int val){
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
void insert(AVLTree*t, int value){
    AVLTreeNode**indirect = &(t->root);
    vec_p path = newVec_p();
    while(*indirect != NULL){
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
        if((*indirect)->value > value)
            indirect = &((*indirect)->left);
        else
            indirect = &((*indirect)->right);
    }
   *indirect = mkAVLTreeNode(value);
    path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    balance(t, path);
    t->_size++;
}
void erase(AVLTree*t, int value){
    AVLTreeNode**indirect = &(t->root);
    vec_p path = newVec_p();
    while(*indirect != NULL && (*indirect)->value != value){
        path.ptr = pushback_p(path.ptr, &path.sz, indirect);
        if((*indirect)->value > value)
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
int find(AVLTree*t, int value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while (direct != NULL && direct->value != value){
        if(direct->value > value)
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
int upper_bound(AVLTree*t, int value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while(direct != NULL){
        if(direct->value > value)
           direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    return idx;
}
int lower_bound(AVLTree*t, int value){
    AVLTreeNode*direct = t->root;
    int idx = 0;
    while(direct != NULL){
        if(direct->value >= value)
           direct = direct->left;
        else{
            idx += (direct->left ? direct->left->count : 0) + 1;
            direct = direct->right;
        }
    }
    return idx;
}
int operatorAt(AVLTree*t, size_t idx){
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
int TESTmain(){
    AVLTree tree = newAVLTree();
    for(int i=0; i <11; i++){
        int x = rand();
        insert(&tree, x);
    }
    for(int i=0; i < size(&tree); i++){
        int pi = operatorAt(&tree, i);
        printf("%d\n", pi);
    }
    clear(&tree);
    printf("%d\n", size(&tree));
    return 0;
}
#endif


int lis(int*a, int asz){
  AVLTree st = newAVLTree();
  for(int i=0; i<asz; ++i){
    int it = lower_bound(&st, a[i]);
    if(it!=size(&st))
      erase(&st, operatorAt(&st, it));
    insert(&st, a[i]);
  }
  return size(&st);
}
int main(){
  int T;
  scanf("%d", &T);
  for(int t=1; t<=T; ++t){
    printf("Case %d: ", t);
    int n, p, q;
    scanf("%d %d %d", &n, &p, &q);
    int board[n][n]; dfill(board, n, n, -1);
    for(int i=0; i<p+1; ++i){
      int x;
      scanf("%d", &x);
      x--;
      board[x/n][x%n] = i;
    }
    veci pseq = newVeci();
    for(int i=0; i<q+1; ++i){
      int x;
      scanf("%d", &x);
      x--;
      if(board[x/n][x%n] != -1)
        pb(pseq, board[x/n][x%n]);
    }
    printf("%d\n", lis(pseq.ptr, pseq.sz));
  }
  return 0;
}
