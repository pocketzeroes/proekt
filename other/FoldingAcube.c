#pragma GCC optimize "-O3"
#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>

typedef long long ll;

ll min(ll a, ll b){return a<b?a:b;}



ll from_file(){
    ll piece = 0;
    for(int r=0; r<6; r++){
        for(int c=0; c<6; c++){
            char ch = getchar();
            if(ch == '#')
                piece ^= 1ll << (8ll * r+c);
        }
        getchar();
    }
    return piece;
}
ll justify_top(ll x){
    while((x&0xff) == 0)
        x >>= 8;
    return x;
}
ll justify_left(ll x){
    while((x&0x0101010101010101) == 0)
        x >>= 1;
    return x;
}
ll transpose(ll x){
    x ^= (x & 0x00aa00aa00aa00aa) << 7 ;
    x ^= (x >> 7) & 0x00aa00aa00aa00aa ;
    x ^= (x & 0x00aa00aa00aa00aa) << 7 ;
    x ^= (x & 0x0000cccc0000cccc) << 14;
    x ^= (x >> 14) & 0x0000cccc0000cccc;
    x ^= (x & 0x0000cccc0000cccc) << 14;
    x ^= (x & 0x00000000f0f0f0f0) << 28;
    x ^= (x >> 28) & 0x00000000f0f0f0f0;
    x ^= (x & 0x00000000f0f0f0f0) << 28;
    return x;
}
ll vertical_reflect(ll x){
    x ^= (x & 0xffffffff00000000) >> 32;
    x ^= (x & 0x00000000ffffffff) << 32;
    x ^= (x & 0xffffffff00000000) >> 32;
    x ^= (x & 0xffff0000ffff0000) >> 16;
    x ^= (x & 0x0000ffff0000ffff) << 16;
    x ^= (x & 0xffff0000ffff0000) >> 16;
    x ^= (x & 0xff00ff00ff00ff00) >> 8 ;
    x ^= (x & 0x00ff00ff00ff00ff) << 8 ;
    x ^= (x & 0xff00ff00ff00ff00) >> 8 ;
    return x;
}
ll canonical_d4(ll x){
    x = justify_top (x);
    x = justify_left(x);
    ll best = x;
    for(int ii=0; ii<5; ii++){
        x = transpose(x);
        best = min(best, x);
        if(ii == 3)
            break;
        x = vertical_reflect(x);
        x = justify_top(x);
        best = min(best, x);
    }
    return best;
}
typedef struct{
  ll   first;
  bool second;
}pair;

bool cubable_hexomino(ll piece){
    pair D[35] = {
            {    63, false },
            {   287, false },
            {   543, false },
            {   783, false },
            {   798, false },
            {  1055, false },
            {  1295, false },
            {  1551, false },
            {  1799, false },
            {  1805, false },
            {  1806, false },
            {  1820, true  },
            {  2319, false },
            { 65807, false },
            { 66311, false },
            { 66318, false },
            { 66823, false },
            { 67331, false },
            { 67333, false },
            { 67334, false },
            { 67340, true  },
            { 69377, true  },
            { 69378, true  },
            { 69380, true  },
            { 69384, true  },
            {131599, false },
            {131854, false },
            {132867, false },
            {132869, false },
            {132876, true  },
            {134659, true  },
            {134914, true  },
            {134916, true  },
            {197134, false },
            {198156, true  }
        };
    piece = canonical_d4(piece);

    bool found = false;
    bool dpiece=false;
    for(int i=0;i<35;i++){
        if(D[i].first == piece){
            found=true;
            dpiece = D[i].second;
            break;
        }
    }
    if(!found)
        return false;
    return dpiece;
}

int main(){
    ll piece = from_file();

    if(cubable_hexomino(piece))
        puts("can fold");
    else
        puts("cannot fold");
    return 0;
}
