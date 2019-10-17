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

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
ll Line_x;
typedef struct{ // Line
  int x1, x2, y1, y2, i;
}Line;
int cmpL(Line this, Line l){
  ll diff = ((this.y1-l.y1)*(this.x2-this.x1) +
            (this.y2-this.y1)*(Line_x-this.x1))*(l.x2-l.x1) -
            (l.y2-l.y1)*(Line_x-l.x1)*(this.x2-this.x1);
  if(diff > 0)
    return(this.x2-this.x1)*(l.x2-l.x1);
  if(diff < 0)
    return-(this.x2-this.x1)*(l.x2-l.x1);
  return 0;
}
#if 1// set
typedef struct AVLTreeNode{
  struct AVLTreeNode*left;
  struct AVLTreeNode*right;
  Line value;
  int count;
  int height;
}AVLTreeNode;
AVLTreeNode newAVLTreeNode(Line val){
  AVLTreeNode rez;
  rez.value  = val;
  rez.count  = 1;
  rez.height = 1;
  rez.left   = NULL;
  rez.right  = NULL;
  return rez;
}
AVLTreeNode*mkAVLTreeNode(Line val){
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
void insert(AVLTree*t, Line value){
  AVLTreeNode**indirect = &(t->root);
  vec_p path = newVec_p();
  while(*indirect != NULL){
    path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    if(cmpL((*indirect)->value, value)>0)
      indirect = &((*indirect)->left);
    else
      indirect = &((*indirect)->right);
  }
 *indirect = mkAVLTreeNode(value);
  path.ptr = pushback_p(path.ptr, &path.sz, indirect);
  balance(t, path);
  t->_size++;
}
void erase(AVLTree*t, Line value){
  AVLTreeNode**indirect = &(t->root);
  vec_p path = newVec_p();
  while(*indirect != NULL &&cmpL((*indirect)->value, value)!=0){
    path.ptr = pushback_p(path.ptr, &path.sz, indirect);
    if(cmpL((*indirect)->value, value)>0)
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
int find(AVLTree*t, Line value){
  AVLTreeNode*direct = t->root;
  int idx = 0;
  while (direct != NULL && cmpL(direct->value, value)!=0){
    if(cmpL(direct->value, value)>0)
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
int upper_bound(AVLTree*t, Line value){
  AVLTreeNode*direct = t->root;
  int idx = 0;
  while(direct != NULL){
    if(cmpL(direct->value, value)>0)
     direct = direct->left;
    else{
      idx += (direct->left ? direct->left->count : 0) + 1;
      direct = direct->right;
    }
  }
  return idx;
}
int lower_bound(AVLTree*t, Line value){
  AVLTreeNode*direct = t->root;
  int idx = 0;
  while(direct != NULL){
    if(cmpL(direct->value, value)>=0)
      direct = direct->left;
    else{
      idx += (direct->left ? direct->left->count : 0) + 1;
      direct = direct->right;
    }
  }
  return idx;
}
Line operatorAt(AVLTree*t, size_t idx){
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
///////////////////////////////////////////////

typedef struct{ // Event
  int x, i;
  bool start;
}Event;
int cmpE(const void*pa, const void*pb){
  Event*this=(Event*)pa;
  Event*e   =(Event*)pb;
  int diff = this->x - e->x;
  if(diff == 0)
    return(e->start?1:0) - (this->start?1:0);
  return diff;
}

int main(){
  int N = in_nextInt();
  Line  lines [N];
  Event events[2*N];
  for(int i=0; i<N; ++i){
    lines[i].x1         = in_nextInt();
    lines[i].y1         = in_nextInt();
    lines[i].x2         = in_nextInt();
    lines[i].y2         = in_nextInt();
    lines[i].i          = i;
    events[2*i].x       = lines[i].x1;
    events[2*i].i       = i;
    events[2*i].start   = lines[i].x1<lines[i].x2;
    events[2*i+1].x     = lines[i].x2;
    events[2*i+1].i     = i;
    events[2*i+1].start = lines[i].x2<lines[i].x1;
  }
  int x0 = in_nextInt();
  qsort(events, 2*N, sizeof(Event), cmpE);
  AVLTree now = newAVLTree();//of Line
  int next[N+1]; clr(next);
  for(int i=0; i<2*N; ++i){
    if(events[i].start){
      Line_x = events[i].x;
      int abov = lower_bound(&now, lines[events[i].i]);
      if(abov == size(&now)){
        next[events[i].i] = next[N];
        next[N] = events[i].i;
      }
      else{
        Line above = operatorAt(&now, abov);
        next[events[i].i] = next[above.i];
        next[above.i]     = events[i].i;
      }
      insert(&now, lines[events[i].i]);
    }
    else
      erase(&now, lines[events[i].i]);
  }
  int p = N;
  for(int i=0; i<N; ++i){
    p = next[p];
    if(x0 >= lines[p].x1 && x0 <= lines[p].x2||
       x0 <= lines[p].x1 && x0 >= lines[p].x2){
      Line l = lines[p];
      if(lines[p].y1 < lines[p].y2)
        x0 = lines[p].x1;
      else
        x0 = lines[p].x2;
    }
  }
  printf("%d\n", x0);
  return 0;
}
