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
typedef long long ll;
ll psum[100005];

ll total(long long a, long long b) {
    return (b * (b + 1) - a * (a - 1)) / 2;
}
int minMoves(int* nums, int numsSz, int k){
    ll res =(ll)1e18;
    int o = 0;
    int*ones=NULL;
    for(int i = 0; i < numsSz; i++){
        if (nums[i] == 1) {
            psum[o + 1] = psum[o] + i;
            sb_push(ones, i);
            o++;
        }
    }
    for(int start = 0; start + k <= sb_count(ones); start++){
        int midx = start + k / 2;
        int m1 = ones[midx];
        ll sum = 0;
        int m2 = k / 2;
        if (m2 > 0){
            sum += total(m1 - m2, m1 - 1) - (psum[midx] - psum[start]);
        }
        int greater = k - m2 - 1;
        if (greater > 0) {
            sum += (psum[start + k] - psum[midx + 1]) - total(m1 + 1, m1 + greater);
        }
        res = fminl(res, sum);
    }
    return res;
}
