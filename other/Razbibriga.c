#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ mxn = 26};
int count[mxn][mxn];

int main(){
  int n;
  scanf("%d", &n);
  char word[20];
  for(int i = 0; i < n; i++){
    scanf( "%s", word );
    count[word[0]-'A'][word[strlen(word)-1]-'A']++;
  }
  int firstLevel, secondLevel, thirdLevel;
  long long ret = 0;
  for( int upperLeft = 0; upperLeft < mxn; upperLeft++ ){
    for( int upperRight = 0; upperRight < mxn; upperRight++ ){
      firstLevel = count[upperLeft][upperRight];
      count[upperLeft][upperRight]--;
      for( int lowerLeft = 0; lowerLeft < mxn; lowerLeft++ ){
        secondLevel = count[upperLeft][lowerLeft];
        count[upperLeft][lowerLeft]--;
        for( int lowerRight = 0; lowerRight < mxn; lowerRight++ ){
          thirdLevel = count[upperRight][lowerRight]--;
          ret += (long long)count[lowerLeft][lowerRight] * firstLevel * secondLevel * thirdLevel;
          count[upperRight][lowerRight]++;
        }
        count[upperLeft][lowerLeft]++;
      }
      count[upperLeft][upperRight]++;
    }
  }
  printf("%lld\n", ret);
  return 0;
}
