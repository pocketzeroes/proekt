#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>

typedef uint32_t u32;
typedef uint64_t u64;

enum{ MOD_BASE = 1000000007};
typedef struct{
  u32 bits[2049];
  u32 cnt;
}BitVec,*pBitVec;

BitVec bitvecs[20];
u32 max[65536];
u32 twohat[17] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
u32 masks[32] ={
  0x00000001, 0x00000002, 0x00000004, 0x00000008,
  0x00000010, 0x00000020, 0x00000040, 0x00000080,
  0x00000100, 0x00000200, 0x00000400, 0x00000800,
  0x00001000, 0x00002000, 0x00004000, 0x00008000,
  0x00010000, 0x00020000, 0x00040000, 0x00080000,
  0x00100000, 0x00200000, 0x00400000, 0x00800000,
  0x01000000, 0x02000000, 0x04000000, 0x08000000,
  0x10000000, 0x20000000, 0x40000000, 0x80000000
};

void init(pBitVec pbv, int n){
  int i;
  u32 *p = &(pbv->bits[0]);
  for(i = 0; i < n; i++)
    *p++ = 0;
  pbv->cnt = 0;
}
void SetCnt(pBitVec pbv, int n){
  u32 mask;
  int index;
  if((n >= 1) && (n <= 65536)) {
    n--;
    index = n >> 5;
    mask = masks[n & 0x1f];
    if((pbv->bits[index] & mask) == 0) {
      pbv->bits[index] |= mask;
      pbv->cnt++;
    }
  }
}
int Intersect(pBitVec pbv1, pBitVec pbv2, u32 cnt){
  u32 *p1, *p2;
  u32 i;
  p1 = &(pbv1->bits[0]);
  p2 = &(pbv2->bits[0]);
  for(i = 0; i < cnt ; i++, p1++, p2++) {
    if((*p1 & *p2) != 0)
      return 1;
  }
  return 0;
}
int CheckUnion(pBitVec pbv1, pBitVec pbv2, int n){
  u32 *p1, *p2;
  u32 i, cnt, rem;
  p1 = &(pbv1->bits[0]);
  p2 = &(pbv2->bits[0]);
  cnt = (n >> 5);
  rem = n & 0x1f;
  for(i = 0; i < cnt ; i++, p1++, p2++) {
    if((*p1 | *p2) != 0xffffffff)
      return -1;
  }
  if(rem > 0) {
    rem = (1 << (rem)) - 1;
    if((*p1 | *p2) != rem)
      return -2;
  }
  return 0;
}
int Compare(int start1, int start2, int cnt){
  int i;
  u32 *p1, *p2;
  for(i = 0, p1 = &(max[start1]), p2 = &(max[start2]) ; i < cnt ; i++, p1++, p2++) {
    if(*p1 != *p2)
      return -1;
  }
  return 0;
}
u32 ChkSolve(u32 start, u32 cnt, int nvals, int level){
  u32 cntr, swtch, *p, icnt;
  u32 ret = 0;
  u64 tval;
  pBitVec pbv1, pbv2;
  pbv1 = &bitvecs[0];
  pbv2 = &bitvecs[1];
  icnt = (nvals >> 5) + 1;
  init(pbv1, icnt);
  init(pbv2, icnt);
  p = &(max[start]);
  swtch = cnt/2;
  for(cntr = 0; cntr < cnt; cntr++, p++) {
    if(cntr < swtch)
      SetCnt(pbv1, *p);
    else
      SetCnt(pbv2, *p);
  }
  if(Intersect(pbv1, pbv2, icnt) != 0) {
    if(Compare(start, start + (cnt+1)/2, cnt/2) != 0)
      return 0;
    else {
      if(pbv2->cnt == 1)
        return twohat[level];
      else {
        tval = ChkSolve(start + cnt/2, (cnt+1)/2, nvals, level - 1);
        return (u32)((2*tval) % MOD_BASE);
      }
    }
  }
  else if(pbv1->cnt == 1) {
    tval = twohat[level - 1];
    if(pbv2->cnt == 1) {
      tval *= twohat[level-1];
      return (u32)(tval % MOD_BASE);
    }
    else {
      tval *= ChkSolve(start + cnt/2, (cnt+1)/2, nvals, level - 1);
      return (u32)(tval % MOD_BASE);
    }
  }
  else if(pbv2->cnt == 1) {
    tval = twohat[level - 1];
    tval *= ChkSolve(start, cnt/2, nvals, level - 1);
    return (u32)(tval % MOD_BASE);
  }
  else {
    if((tval = ChkSolve(start, cnt/2, nvals, level - 1)) != 0) {
      tval  *= ChkSolve(start + cnt/2, (cnt+1)/2, nvals, level - 1);
      return (u32)(tval % MOD_BASE);
    }
    else
      return 0;
  }
}
int main(){
  int m, n, i;
  u32 ind, two_m, two_m2, cnt, ret;
  u64 tval;
  pBitVec pbv1, pbv2;
  if(scanf("%d %d", &m, &n) != 2)
    return -1;
  if((m < 0) || (m > 16) || (n < 1) || (n > (int)twohat[m]))
    return -2;
  if(m == 0)
    return puts("1")*0;
  pbv1   = &bitvecs[0];
  pbv2   = &bitvecs[1];
  two_m  = twohat[m];
  two_m2 = twohat[m-1];
  cnt = (n >> 5) + 1;
  init(pbv1, cnt);
  init(pbv2, cnt);
  for(ind = 0; ind < two_m ; ind++) {
    if(scanf("%d", &i) != 1)
      return -3;
    max[ind] = i;
    if(ind < two_m2)
      SetCnt(pbv1, i);
    else
      SetCnt(pbv2, i);
  }
  if(CheckUnion(pbv1, pbv2, n) != 0)
    ret = 0;
  else if(Intersect(pbv1, pbv2, cnt) != 0) {
    if(Compare(0, two_m2, two_m2) != 0)
      ret = 0;
    else {
      if(pbv2->cnt == 1)
        ret = twohat[m];
      else {
        tval = ChkSolve(two_m2, two_m2, n, m-1);
        ret = (u32)((2*tval) % MOD_BASE);
      }
    }
  }
  else if(pbv1->cnt == 1) {
    tval = twohat[m-1];
    if(pbv2->cnt == 1) {
      tval *= twohat[m-1];
      ret = (u32)(tval % MOD_BASE);
    }
    else {
      tval *= ChkSolve(two_m2, two_m2, n, m-1);
      ret = (u32)(tval % MOD_BASE);
    }
  }
  else if(pbv2->cnt == 1) {
    tval = twohat[m-1];
    tval *= ChkSolve(0, two_m2, n, m-1);
    ret = (u32)(tval % MOD_BASE);
  }
  else {
    if((tval = ChkSolve(0, two_m2, n, m-1)) != 0) {
      tval  *= ChkSolve(two_m2, two_m2, n, m-1);
      ret = (u32)(tval % MOD_BASE);
    }
    else
      ret = 0;
  }
  printf("%lu\n", ret);
  return 0;
}
