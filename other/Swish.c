#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
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

int n;
pair*cards;
const int MAX = INT_MAX;
int positionsPerColor[4] = {4, 2, 4, 2};


pair rotate180(pair p){
  return newPair(11 - p.first, 11 - p.second);
}
pair vertical_flip(pair p){
  return newPair(p.first + (p.first/3) * -6 + 9, p.second + (p.second/3) * -6 + 9);
}
int getColor(int x){
  if (x == 0 || x == 2 || x == 9 || x == 11)
    return 0;
  else if (x == 3 || x == 5 || x == 6 || x == 8)
    return 2;
  else if (x == 1 || x == 10)
    return 1;
  else
    return 3;
}
bool backTrack(int cardsToUse, int*placed, int dotPosition){
  if (cardsToUse == 0) {
    for (int i = 0; i < 12; i++) 
      if (placed[i] != 0 && placed[i] != 3) 
        return false;
    return true;
  }
  pair c[4]; memset(c, 0, sizeof(c));
  for (int i = 0; i < n; i++) {
    if (((cardsToUse>>i)&1)==1 && getColor(cards[i].first) == getColor(dotPosition) && (placed[dotPosition]&2) == 0) {
      c[0] = cards[i];
      c[1] = rotate180(cards[i]);
      c[2] = vertical_flip(cards[i]);
      c[3] = vertical_flip(c[1]);
      cardsToUse &= (~(1<<i));
      placed[dotPosition] |= 2;
      for (int j = 0; j < 4; j++) {
        if ((c[j].first == dotPosition)  && (placed[c[j].second]&1) == 0) {
          placed[c[j].second] |= 1;
          if (backTrack(cardsToUse, placed, c[j].second))
            return true;
          placed[c[j].second] &= ~1;
        } 
      }
      placed[dotPosition] &= ~2;
      cardsToUse |= (1<<i);
    }
  }
  return false;
}
bool makesASwish(int cardsChosen){
  if (cardsChosen == 0)
    return false;
  int dots [4]={0};
  int rings[4]={0};
  for (int i = 0; i < n; i++) {
    if (((cardsChosen>>i)&1) == 1) {
      dots [getColor(cards[i].second)]++;
      rings[getColor(cards[i].first )]++;
    }
  }
  for (int i = 0; i < 4; i++) {
    if (dots[i] != rings[i] || dots[i] > positionsPerColor[i])
      return false;
  }
  int placed[12]={0};
  for (int i = 0; i < n; i++) {
    if (((cardsChosen>>i)&1) == 1) {
      placed[cards[i].first] |= 2;
      placed[cards[i].second] |= 1;
      return backTrack((cardsChosen&(~(1<<i))), placed, cards[i].second);
    }
  }
  return false;
}

int main(){
  n = in_nextInt();
  cards = calloc(n, sizeof(pair));
  for (int i = 0; i < n; i++){
    cards[i] = newPair(in_nextInt(), in_nextInt());
  }
  int dp[1<<n];
  fill(dp, 1<<n, MAX);
  vec relevant = newVec();
  relevant.ptr = pushback(relevant.ptr, &relevant.sz, 0);
  dp[0] = 0;
  for (int i = 0; i < (1<<n); i++){
    if (makesASwish(i)){
      for(int j = relevant.sz-1; j >= 0; j--){
        int key = relevant.ptr[j];
        if( (i&key)==0 && (dp[key] != MAX) && dp[key]+1 <dp[key|i]){
          if(dp[i|key] == MAX)
            relevant.ptr = pushback(relevant.ptr, &relevant.sz, i|key);
          dp[i|key] = dp[key]+1;
        }
      }
    }
  }
  printf("%d\n", (dp[(1<<n)-1] != MAX ? dp[(1<<n)-1] : -1));
  return 0;
}