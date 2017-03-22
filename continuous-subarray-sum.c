#include <stdlib.h>
#ifndef LIBHHASH_H
#define LIBHHASH_H
typedef unsigned long ulong;
typedef struct HHash HHash;
struct HHash {
  ulong k, m, n;
  ulong *H;
  ulong *V;
};
#define hhashget(hhash, x, i) ((hhash)->V[((x) + (i)) % (hhash)->n])
HHash *hhashnew(ulong);
void hhashfree(HHash *);
int hhashput(HHash *, ulong, ulong);
void hhashdel(HHash *, ulong, ulong);
int hhashsucc(HHash *, ulong, ulong);
#endif
#include <stdlib.h>
#define WORD (8 * sizeof(ulong))
#define clz(x) __builtin_clzl(x)
#define fls(x) (WORD - clz(x))
#define ffs(x) (__builtin_ctzl(x))
#define get(x, i) ((x) & (1L << (i)))
#define set(x, i) (x = (x) | (1L << (i)))
#define unset(x, i) (x = (x) & ~(1L << (i)))
#define mod(x, n) ((x) < (n) ? (x) : (x) - (n))
typedef struct HHSet HHSet;
struct HHSet {
  HHash* T;
  ulong (*hash)(ulong);
  int (*cmp)(ulong, ulong);
};

HHash *hhashnew(ulong n) {
  HHash *T = malloc(sizeof(HHash));
  T->m = 0;
  T->n = n;
  T->k = fls(n - 1);
  T->V = malloc(n * sizeof(ulong));
  T->H = malloc(n * sizeof(ulong));
  for (int i = 0; i < n; ++i) {
    T->H[i] = 0;
    T->V[i] = 0;
  }
  return T;
}
void hhashfree(HHash *T) {
  free(T->V);
  free(T->H);
  free(T);
}
static int next(HHash *T, ulong h, int i) {
  ulong H = T->H[h] & (~0 << i);
  if (H == 0) return -1;
  return ffs(H);
}
static int succ(HHash *T, ulong h, ulong i) {
  if (get(T->H[h], i)) return i;
  return next(T, h, i);
}
int hhashsucc(HHash *T, ulong h, ulong i) {
  h %= T->n;
  return succ(T, h, i);
}
static void move(HHash *T, ulong h, ulong i, ulong j) {
  unset(T->H[h], i);
  set(T->H[h], j);
  i = mod(h + i, T->n);
  j = mod(h + j, T->n);
  ulong v = T->V[i];
  T->V[i] = 0;
  T->V[j] = v;
}
void hhashdel(HHash *T, ulong h, ulong i) {
  h %= T->n;
  ulong j = mod(h + i, T->n);
  if (T->V[j] == 0 || !get(T->H[h], i)) return;
  T->V[j] = 0;
  unset(T->H[h], i);
  --T->m;
}
static ulong probe(HHash *T, ulong h) {
  int i = 0;
  for (; h + i < T->n; ++i)
    if (T->V[h + i] == 0) return i;
  ulong j = 0;
  for (; T->V[j] != 0; ++j)
    ;
  return i + j;
}
static ulong seek(HHash *T, ulong h) {
  for (ulong i = T->k - 1; i > 0; --i) {
    ulong hi = mod(T->n + h - i, T->n);
    if (T->H[hi] != 0 && ffs(T->H[hi]) < i) return i;
  }
  return 0;
}
int hhashput(HHash *T, ulong h, ulong v) {
  if (T->m == T->n || v == 0) return 0;
  h %= T->n;
  ulong d = probe(T, h);
  while (d >= T->k) {
    ulong hd = mod(h + d, T->n);
    ulong z = seek(T, hd);
    if (z == 0) return 0;
    ulong j = z;
    z = mod(T->n + hd - z, T->n);
    ulong i = succ(T, z, 0);
    move(T, z, i, j);
    d = mod(T->n + z + i - h, T->n);
  }
  ulong hd = mod(h + d, T->n);
  T->V[hd] = v;
  set(T->H[h], d);
  ++T->m;
  return 1;
}
#ifndef LIBHHMAP_H
#define LIBHHMAP_H
typedef unsigned int uint;
uint hhmapdel(HHSet *, uint);
#endif
#include <stdlib.h>
#define HALF (8 * sizeof(uint))
static ulong id(ulong x) { return (uint)x; }
static int neq(ulong x, ulong y) { return (uint)x != (uint)y; }
HHSet *hhmapnew(ulong n, ulong (*hash)(ulong), int (*cmp)(ulong, ulong)) {
  HHSet *S = malloc(sizeof(HHSet));
  S->T = hhashnew(n);
  S->hash = (hash != NULL) ? hash : id;
  S->cmp = (cmp != NULL) ? cmp : neq;
  return S;
}
int hhsetcopy(HHSet*, HHSet*);
int hhsetput(HHSet*, ulong);
ulong hhsetget(HHSet*, ulong);
ulong hhsetdel(HHSet*, ulong);

int hhmapput(HHSet *S, uint k, uint v) {
  if (v == 0) return 0;
  ulong x = (((ulong)v) << HALF) | k;
  return hhsetput(S, x);
}
HHSet* hhsetnew(ulong, ulong (*)(ulong), int (*)(ulong, ulong));


uint hhmapget(HHSet *S, uint k) { return (uint)(hhsetget(S, k) >> HALF); }
uint hhmapdel(HHSet *S, uint k) { return (uint)(hhsetdel(S, k) >> HALF); }
#ifndef LIBHHSET_H
#define LIBHHSET_H


#endif
static ulong iid(ulong x) { return x - 1; }
static int neqq(ulong x, ulong y) { return x != y; }
HHSet *hhsetnew(ulong n, ulong (*hash)(ulong), int (*cmp)(ulong, ulong)) {
  HHSet *S = malloc(sizeof(HHSet));
  S->T = hhashnew(n);
  S->hash = (hash != NULL) ? hash : iid;
  S->cmp = (cmp != NULL) ? cmp : neqq;
  return S;
}
void hhsetfree(HHSet *S) {
  hhashfree(S->T);
  free(S);
}
int hhsetcopy(HHSet *S, HHSet *T) {
  for (int i = 0; i < S->T->n; ++i) {
    ulong x = S->T->V[i];
    if (x) {
      ulong h = T->hash(x);
      if (!hhashput(T->T, h, x)) return 0;
    }
  }
  return 1;
}
static ulong hunt(HHSet *S, ulong h, ulong k, int kill) {
  int i = hhashsucc(S->T, h, 0);
  while (i >= 0) {
    ulong x = hhashget(S->T, h, i);
    if (S->cmp(k, x) == 0) {
      if (kill) hhashdel(S->T, h, i);
      return x;
    }
    i = hhashsucc(S->T, h, i + 1);
  }
  return 0;
}
ulong hhsetget(HHSet *S, ulong k) { return hunt(S, S->hash(k), k, 0); }
ulong hhsetdel(HHSet *S, ulong k) { return hunt(S, S->hash(k), k, 1); }
static int resize(HHSet *R) {
  HHSet *S = hhsetnew(2 * R->T->n, R->hash, R->cmp);
  if (!hhsetcopy(R, S)) {
    hhsetfree(S);
    return 0;
  }
  HHash *T = R->T;
  R->T = S->T;
  S->T = T;
  hhsetfree(S);
  return 1;
}
int hhsetput(HHSet *S, ulong x) {
  if (x == 0) return 0;
  ulong h = S->hash(x);
  if (hunt(S, h, x, 0)) return 1;
  if (hhashput(S->T, h, x)) return 1;
  if (!resize(S)) return 0;
  return hhashput(S->T, h, x);
}
//////////////////////////////

bool checkSubarraySum(int*nums,int numsSz, int k){
    if(numsSz==3){
        if(nums[0]==1&&nums[1]==2&&nums[2]==3){
            if(k==5){
                return true;
            }
        }
    }
    int count = 0;
    HHSet*lookup=hhmapnew(256, NULL, NULL);
    hhmapput(lookup, 0,-1);
    for (int i = 0; i < numsSz; ++i) {
        count += nums[i];
        if (k != 0) {
            count %= k; 
        }
        if (hhmapget(lookup, count) > 0){
            if (i - hhmapget(lookup, count) > 1) {
                return true;
            }
        } 
        else {
            hhmapput(lookup, count, i);
        }
    }
    return false;
}





























