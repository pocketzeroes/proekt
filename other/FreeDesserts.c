#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
ll****newmat(int a, int b, int c, int d){
  ll****rv = calloc(a, sizeof(ll***));
  for(int i1=0; i1<a; i1++){
    rv[i1] = calloc(b, sizeof(ll**));
    for(int i2=0; i2<b; i2++){
      rv[i1][i2] = calloc(c, sizeof(ll*));
      for(int i3=0; i3<c; i3++)
        rv[i1][i2][i3] = calloc(d, sizeof(ll));
    }
  }
  return rv;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int n;

ll    sum;
int*  sumDigits; int sumDigits_len;
ll****memo;
int   maskSum;
int*  bitValues;
int   printCount;



ll convert(int*a){
  ll res = 0L;
  for(int i=n-1; i>=0; i--)
    res = 10*res + a[i];
  return res;
}
void printOut(int*a, int*b){
  printf("%lld %lld\n", convert(a), convert(b));
}
void print(int maskA, int maskB, int*a, int*b, int k, int carry, bool eq){
  if (printCount >= 5000)
    return;
  if (k == -1 && carry == 0) {
    printOut(a, b);
    printCount++;
    return;
  }
  if (k == -1)
    return;
  int unusedMask = (1<<10) - 1 - maskA - maskB;
  for (int i=0; i<10; i++) {
    if (i>0 && (((1<<i) & maskSum) != 0))
      continue;
    if (i>0 && (((1<<i) & maskB) != 0))
      continue;
    if (i == 0 && maskA !=0 && (((1<<i) & maskSum) != 0))
      continue;
    if (i == 0 && maskA !=0 && (((1<<i) & maskB) != 0))
      continue;
    int digitB = 0;
    if (carry == 1)
      digitB = 10 + sumDigits[k] - i;
    else
      digitB = sumDigits[k] - i;
    for (int myC=0; myC<2; myC++){
      int myB = digitB-myC;
      if (myB < 0 || myB >= 10)
        continue;
      if ( ((((1<<myB) & maskA)) != 0) || ((((1<<myB) & maskSum)) != 0) )
        continue;
      if (i == myB && i != 0)
        continue;
      if (i == myB && i == 0 && (maskA != 0 && maskB != 0))
        continue;
      int newMaskA = (maskA | (1<<i));
      if (maskA == 0 && i == 0)
        newMaskA = 0;
      int newMaskB = (maskB | (1<<myB));
      if (maskB == 0 && myB == 0)
        newMaskB = 0;
      a[k] = i;
      b[k] = myB;
      if (eq && a[k] > b[k])
        continue;
      bool newEq = !eq ? false : true;
      if (newEq && a[k] < b[k])
        newEq = false;
      print(newMaskA, newMaskB, a, b, k-1, myC, newEq);
      if (printCount >= 5000)
        return;
    }
  }
}
int compress(int mask){
  int res = 0;
  for (int i=0; i<10; i++)
    if ((mask & (1<<i)) != 0)
      res |= (1<<(bitValues[i]));
  return res;
}
ll isValid(int k, int carry, int lastZero, int maskA){
  if (lastZero == 1)
    return 0L;
  if (k == sumDigits_len && carry == 0)
    return 1L;
  if (k == sumDigits_len-1 && carry == 1 && sumDigits[sumDigits_len-1] == 1)
    return 1L;
  if (k == sumDigits_len)
    return 0L;
  for (int i=k; i<sumDigits_len-1; i++)
    if (sumDigits[i] != 0 || (((1<<9) & maskA) != 0) || (((1<<9) & maskSum) != 0))
      return 0;
  if (carry == 0)
    return 0;
  int lastB = sumDigits[sumDigits_len-1]-1;
  if (lastB == 0)
    lastB = 9;
  if( (((1<<lastB) & maskA) != 0) || (((1<<lastB) & maskSum) != 0) )
    return 0;
  return 1;
}
ll solve(int maskA, int maskB, int k, int carry, int lastZero){
  int maskAcode = compress(maskA);
  int maskBcode = compress(maskB);
  ll res = isValid(k, carry, lastZero, maskA);
  if (k == sumDigits_len)
    return res;
  if (k == sumDigits_len-1 && carry == 1 && sumDigits[sumDigits_len-1] == 1)
    return res;
  if (memo[maskAcode][maskBcode][k][2*carry+lastZero] != -1)
    return memo[maskAcode][maskBcode][k][2*carry+lastZero];
  int unusedMask = (1<<10) - 1 - maskA - maskB;
  for (int i=0; i<10; i++){
    if (((1<<i) & maskSum) != 0)
      continue;
    if (((1<<i) & maskB) != 0)
      continue;
    int digitB = (sumDigits[k] - carry - i + 10)%10;
    if (i > digitB && k == sumDigits_len-1)
      break;
    if (i > digitB && k == sumDigits_len-2 && i+digitB+carry > 9 && sumDigits[sumDigits_len-1] == 1)
      break;
    if (i == digitB)
      continue;
    if ( ((((1<<digitB) & maskA)) != 0) || ((((1<<digitB) & maskSum)) != 0) )
      continue;
    int thisCarry = 0;
    if (i + carry + digitB >= 10)
      thisCarry = 1;
    int last = 0;
    if (i == 0)
      last = 1;
    res += solve(maskA | (1<<i), maskB | (1<<digitB), k+1, thisCarry, last);
  }
  memo[maskAcode][maskBcode][k][2*carry+lastZero] = res;
  return res;
}

int main(){
  scanf("%lld", &sum);
  ll savesum = sum;
  printCount = 0;
  vec digits = newVec();
  while(sum > 0){
    digits.ptr = pushback(digits.ptr, &digits.sz, (int)(sum%10));
    sum = sum/10;
  }
  bitValues = calloc(10, sizeof(int));
  for(int i=0; i<10; i++)
    bitValues[i] = i;
  sumDigits = calloc(digits.sz, sizeof(int));
  sumDigits_len = digits.sz;
  maskSum = 0;
  for (int i=0; i<digits.sz; i++) {
    sumDigits[i] = digits.ptr[i];
    maskSum = maskSum | (1<<sumDigits[i]);
  }
  for (int i=0; i<10; i++)
    if ((maskSum & (1<<i)) != 0)
      for (int j=i; j<10; j++)
        bitValues[j]--;
  int sub = __builtin_popcount(maskSum);
  memo = newmat(1<<(10-sub), 1<<(10-sub), sumDigits_len, 4);//of ll
  for(int i=0; i<(1<<(10-sub)); i++)
    for(int j=0; j<(1<<(10-sub)); j++)
      for(int k=0; k<sumDigits_len; k++)
        fill(memo[i][j][k], 4, -1);
  printf("%lld\n", solve(0, 0, 0, 0, 0));
  n = sumDigits_len;
  int carry = 0;
  if(sumDigits[sumDigits_len-1] == 1){
    n--;
    carry = 1;
  }
  int a[n]; memset(a, 0, sizeof(a));
  int b[n]; memset(b, 0, sizeof(b));
  print(0, 0, a, b, n-1, carry, true);
  return 0;
}
