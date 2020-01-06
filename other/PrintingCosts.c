#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000001];
char*getln(){
  char*rv = gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}


int m[256];


int main(){
m[' ' ]=   0;
m['!' ]=   9;
m['"' ]=   6;
m['#' ]=  24;
m['$' ]=  29;
m['%' ]=  22;
m['&' ]=  24;
m['\'']=   3;
m['(' ]=  12;
m[')' ]=  12;
m['*' ]=  17;
m['+' ]=  13;
m[',' ]=   7;
m['-' ]=   7;
m['.' ]=   4;
m['/' ]=  10;
m['0' ]=  22;
m['1' ]=  19;
m['2' ]=  22;
m['3' ]=  23;
m['4' ]=  21;
m['5' ]=  27;
m['6' ]=  26;
m['7' ]=  16;
m['8' ]=  23;
m['9' ]=  26;
m[':' ]=   8;
m[';' ]=  11;
m['<' ]=  10;
m['=' ]=  14;
m['>' ]=  10;
m['?' ]=  15;
m['@' ]=  32;
m['A' ]=  24;
m['B' ]=  29;
m['C' ]=  20;
m['D' ]=  26;
m['E' ]=  26;
m['F' ]=  20;
m['G' ]=  25;
m['H' ]=  25;
m['I' ]=  18;
m['J' ]=  18;
m['K' ]=  21;
m['L' ]=  16;
m['M' ]=  28;
m['N' ]=  25;
m['O' ]=  26;
m['P' ]=  23;
m['Q' ]=  31;
m['R' ]=  28;
m['S' ]=  25;
m['T' ]=  16;
m['U' ]=  23;
m['V' ]=  19;
m['W' ]=  26;
m['X' ]=  18;
m['Y' ]=  14;
m['Z' ]=  22;
m['[' ]=  18;
m['\\']=  10;
m[']' ]=  18;
m['^' ]=   7;
m['_' ]=   8;
m['`' ]=   3;
m['a' ]=  23;
m['b' ]=  25;
m['c' ]=  17;
m['d' ]=  25;
m['e' ]=  23;
m['f' ]=  18;
m['g' ]=  30;
m['h' ]=  21;
m['i' ]=  15;
m['j' ]=  20;
m['k' ]=  21;
m['l' ]=  16;
m['m' ]=  22;
m['n' ]=  18;
m['o' ]=  20;
m['p' ]=  25;
m['q' ]=  25;
m['r' ]=  13;
m['s' ]=  21;
m['t' ]=  17;
m['u' ]=  17;
m['v' ]=  13;
m['w' ]=  19;
m['x' ]=  13;
m['y' ]=  24;
m['z' ]=  19;
m['{' ]=  18;
m['|' ]=  12;
m['}' ]=  18;
m['~' ]=   9;
    char*s;
    while(1){
        s=getln();
        if(s==NULL)
            break;
        int ans = 0;
        for(int z=0;s[z];z++){char c = s[z];
            ans += m[c];
        }
        printf("%d\n", ans);
    }
    return 0;
}
