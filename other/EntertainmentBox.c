#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpPa(const void*pa, const void*pb){
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

#endif

#define FOR(i,a,b) for(int i=a;i<(int)(b);i++)

int main(){
    AVLTree reqs = newAVLTree();//of pair
    int N, K, ans=0;
    scanf("%d %d", &N, &K);
    pair*pts = calloc(N, sizeof(pair));
    FOR(n,0,N)
        scanf("%d %d", &pts[n].second, &pts[n].first);
    qsort(pts, N, sizeof(pair), cmpPa);
    FOR(k, 0, K)
        insert(&reqs, newpair(0, k));
    for(int z=0;z<N;z++){pair pt = pts[z];
        int it = upper_bound(&reqs, newpair(pt.second, 1000000000));
        if(it != 0){
            --it;
            pair kk = operatorAt(&reqs, it);
            int k = kk.second;
            erase(&reqs, kk);
            insert(&reqs, newpair(pt.first, k));
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
