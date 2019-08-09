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
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}


ll memo[2][2][10][20];
int*digits;
int number_length;

ll count(int updn, int constrain, int lastdigit, int pos){
    if(pos==number_length)
        return 1;
    if(memo[updn][constrain][lastdigit][pos]<0LL){
        ll c=0;
        int upper = constrain==0 ? 9 : digits[pos];
        for( int d=0; d<=upper; d++){
            int newconstrain = (constrain==1 && d==upper) ? 1 : 0;
            if( updn==0 )
                c += count( d<lastdigit?1:0, newconstrain, d, pos+1 );
            else if( d<=lastdigit )
                c += count( 1, newconstrain, d, pos+1 );
        }
        memo[updn][constrain][lastdigit][pos] = c;
    }
    return memo[updn][constrain][lastdigit][pos];
}
int main(){
    char*number = getstr();
    number_length = strlen(number);
    digits = calloc(number_length, sizeof(int));
    for(int i=0; i<number_length; i++)
        digits[i] = (int)(number[i]-'0');
    bool ishill = true;
    bool down   = false;
    for(int i=1; i<number_length; i++){
        if(digits[i-1] < digits[i] && down)
            ishill = false;
        if(digits[i-1] > digits[i])
            down = true;
    }
    if(ishill){
        for(int i=0; i<10; i++){
            fill(memo[0][0][i], 20, -1);
            fill(memo[0][1][i], 20, -1);
            fill(memo[1][0][i], 20, -1);
            fill(memo[1][1][i], 20, -1);
        }
        printf("%lld\n", count( 0, 1, 0, 0 )-1);
    }
    else
        puts("-1");
    return 0;
}
