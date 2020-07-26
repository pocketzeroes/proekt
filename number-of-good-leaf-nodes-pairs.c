typedef struct TreeNode TreeNode;
#ifndef STB_STRETCHY_BUFFER_H_INCLUDED
#define STB_STRETCHY_BUFFER_H_INCLUDED
#ifndef NO_STRETCHY_BUFFER_SHORT_NAMES
#define sb_free   stb_sb_free
#define sb_push   stb_sb_push
#define sb_count  stb_sb_count
#define sb_add    stb_sb_add
#define sb_last   stb_sb_last
#endif
#define stb_sb_free(a)         ((a) ? free(stb__sbraw(a)),0 : 0)
#define stb_sb_push(a,v)       (stb__sbmaybegrow(a,1), (a)[stb__sbn(a)++] = (v))
#define stb_sb_count(a)        ((a) ? stb__sbn(a) : 0)
#define stb_sb_add(a,n)        (stb__sbmaybegrow(a,n), stb__sbn(a)+=(n), &(a)[stb__sbn(a)-(n)])
#define stb_sb_last(a)         ((a)[stb__sbn(a)-1])
#define stb__sbraw(a) ((int *) (a) - 2)
#define stb__sbm(a)   stb__sbraw(a)[0]
#define stb__sbn(a)   stb__sbraw(a)[1]
#define stb__sbneedgrow(a,n)  ((a)==0 || stb__sbn(a)+(n) >= stb__sbm(a))
#define stb__sbmaybegrow(a,n) (stb__sbneedgrow(a,(n)) ? stb__sbgrow(a,n) : 0)
#define stb__sbgrow(a,n)      (*((void **)&(a)) = stb__sbgrowf((a), (n), sizeof(*(a))))

static void*stb__sbgrowf(void*arr, int increment, int itemsize){
  int dbl_cur = arr ? 2*stb__sbm(arr) : 0;
  int min_needed = stb_sb_count(arr) + increment;
  int m = dbl_cur > min_needed ? dbl_cur : min_needed;
  int*p = (int *) realloc(arr ? stb__sbraw(arr) : 0, itemsize * m + sizeof(int)*2);
  if(p){
    if(!arr)
      p[1] = 0;
    p[0] = m;
    return p+2;
  } 
  else {
    #ifdef STRETCHY_BUFFER_OUT_OF_MEMORY
    STRETCHY_BUFFER_OUT_OF_MEMORY;
    #endif
    return(void*)(2*sizeof(int));
  }
}
#endif

int ans;

int*dfs(TreeNode*root, int distance){
  if(root == NULL)
    return NULL;
  if(root->left == NULL && root->right == NULL){
    int*ret = NULL;
    sb_push(ret, 0);
    return ret;
  }
  int*L = dfs(root->left , distance);
  int*R = dfs(root->right, distance);
  for(int z=0;z<sb_count(L);z++){int x = L[z];
    for(int q=0;q<sb_count(R);q++){int y = R[q];
      if(x + y + 2 <= distance)
        ans++;
    }
  }
  int*ret = NULL;
  for(int z=0;z<sb_count(L);z++){int x = L[z];
    sb_push(ret, x+1);
  }
  for(int q=0;q<sb_count(R);q++){int x = R[q];
    sb_push(ret, x+1);
  }
  sb_free(L);
  sb_free(R);
  return ret;
}
int countPairs(TreeNode*root, int distance){
  ans = 0;
  dfs(root, distance);
  return ans;
}
