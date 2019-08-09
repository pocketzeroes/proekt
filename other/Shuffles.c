#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

int main(){
    int n = in_nextInt();
    bool expected[n+2]; memset(expected, 0, sizeof(expected));
    int nsequences = 0;
    for( int i=0; i<n; i++ ){
        int card = in_nextInt();
        if( !expected[card] )
            ++nsequences;
        expected[card+1] = true;
    }
    int nshuffles = 0;
    while( (1<<nshuffles)<nsequences )
        ++nshuffles;
    printf("%d\n", nshuffles);
    return 0;
}
