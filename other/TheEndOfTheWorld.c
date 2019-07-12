#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

char*disks;

ll remaining(int n, char source, char dest, char other){
    ll moves = 0;
    if(n>0){
        --n;
        if( disks[n]==source )
            moves = (1l<<n)+remaining( n, source, other, dest );
        else if( disks[n]==dest )
            moves = remaining( n, other, dest, source );
        else if( disks[n]==other )
            assert(!"PANIC!! disk n is on the OTHER peg!");
        else
            assert(!"PANIC!! disk n has a weird character!");
    }
    return moves;
}
int main(){
    for(;;){
        disks = getstr();
        if(disks[0]=='X')
            break;
        printf("%lld\n", remaining(strlen(disks), 'A', 'B', 'C'));
    }
    return 0;
}
