#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
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

char*vals = "shdc23456789TJQKA";
int perm[4], dirs;

bool card_less(pair c1, pair c2){
  return c1.first != c2.first ? perm[c1.first] < perm[c2.first] : (c1.second < c2.second ^ (dirs >> c1.first & 1));
}
int main(){
  int n, ans = 99, best[99];
  pair cards[99];
  scanf("%d", &n);
  for (int i = 0; i < n; ++i){
    char buf[9];
    scanf("%s", buf);
    cards[i] = newPair(strchr(vals, buf[1])-vals, strchr(vals, buf[0])-vals);
  }
  for (int i = 0; i < 4; ++i)
    perm[i] = i;
  do{
    for (dirs = 0; dirs < 16; ++dirs){
      for (int i = n-1; i >= 0; --i){
        best[i] = 1;
        for (int j = i+1; j < n; ++j)
          if(card_less(cards[i], cards[j]))
            best[i] = max(best[i], best[j]+1);
        ans = min(ans, n-best[i]);
      }
    }
  }
  while(next_permutation(perm, 4));
  printf("%d\n", ans);
  return 0;
}
