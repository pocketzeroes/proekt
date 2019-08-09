#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
    int o, c, n, l;
}Piece;
Piece newPiece(int o, int c, int l){
    return(Piece){o, c, o-c, l};
}
int cmpP(const void*pa, const void*pb){
    Piece*aa=(Piece*)pa;
    Piece*bb=(Piece*)pb;
    Piece a = *aa;
    Piece b = *bb;
    int diff;
    if( (a.n > 0) ^ (b.n > 0) )
        diff = b.n - a.n;
    else if( a.n > 0 ){
        if( a.c == b.c )
            diff =  b.n - a.n;
        else
            diff =  a.c - b.c;
    }
    else{
        if( a.o == b.o )
            diff =  b.n - a.n;
        else
            diff =  b.o - a.o;
    }
    return diff;
}
int main(){
    int n = in_nextInt();
    int total = 0;
    Piece pieces[n];
    for(int i=0; i<n; i++){
        char*parens = getstr();
        int parens_len=strlen(parens);
        total += parens_len;
        int o = 0;
        int c = 0;
        for(int z=0;parens[z];z++){char p = parens[z];
            if( p=='(' )
                ++o; 
            else if( o>0 )
                --o;
            else
                ++c; 
        }
        pieces[i] = newPiece(o, c, parens_len);
    }
    qsort(pieces, n, sizeof(Piece), cmpP);
    int bestlength[total];
    fill(bestlength, total, -1);
    bestlength[0] = 0;
    for(int z=0;z<n;z++){Piece piece = pieces[z];
        int lower = piece.c;
        if(piece.n<=0){
            for(int i=lower; i<total; i++){
                if( bestlength[i]>=0 ){
                    int newbalance = i + piece.n;
                    if( newbalance>=0 && newbalance<total && bestlength[i]+piece.l>bestlength[newbalance] )
                        bestlength[newbalance] = bestlength[i]+piece.l;
                }
            }
        }
        else{
            for( int i=total-1; i>=lower; i-- ){
                if( bestlength[i]>=0 ){
                    int newbalance = i + piece.n;
                    if( newbalance>=0 && newbalance<total && bestlength[i]+piece.l>bestlength[newbalance] )
                        bestlength[newbalance] = bestlength[i]+piece.l;
                }
            }
        }
    }
    printf("%d\n", bestlength[0]);
    return 0;
}
