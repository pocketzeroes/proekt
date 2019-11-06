#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

void swap(int*nums, int i, int j){
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
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}

char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
int setchrsz(char*str){
    int freq[256]; clr(freq);
    for(int i=0; str[i]; i++){char c=str[i];
        freq[c]++;
    }
    int sum=0;
    for(int i=0; i<256; i++){
        if(freq[i])
            sum++;
    }
    return sum;
}

enum{ MAX_R = 10};
int  cost[MAX_R][MAX_R];
char*team[MAX_R];
int  perm[MAX_R];

int main(){
    int R;
    scanf("%d", &R);
    for(int j=0; j<R; j++){
        team[j] = getstr();
        perm[j] = j;
    }
    for(int a=0; a < R; a++){
        for(int b=0; b < a; b++){
            char*combined = concats(team[a], team[b]);
            int overlap = strlen(combined) - setchrsz(combined);
            cost[a][b] = cost[b][a] = overlap;
        }
    }
    int best = 27*R;
    do{
        int count=0;
        for(int j=0; j<R-1; j++)
            count += cost[perm[j]][perm[j+1]];
        best = fmin(best, count);
    }while(next_permutation(perm, R));
    printf("%d\n", best);
    return 0;
}
