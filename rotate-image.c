#include <stdio.h>

#define X 0x58
#define O 0x20

int m4x4[16][16]={
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,X,X,O,O,O,O,O,O,O,X,X,O,O,O},
    {O,O,X,X,O,O,O,O,O,O,O,X,X,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,O,O,O,O,O,O,O,O},
    {O,O,O,O,O,O,O,X,O,O,O,O,O,O,O,O},
    {O,X,O,O,O,O,O,X,O,O,O,O,O,O,O,O},
    {O,O,X,O,O,O,O,O,O,O,O,O,O,O,O,O},
    {O,O,O,X,O,O,O,O,O,O,O,X,O,O,O,O},
    {O,O,O,O,X,X,X,X,X,X,X,O,O,O,O,O},
    {O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O} 
};
#undef X
#undef O

void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}

void rotate(int matrixRowSize, int matrixColSize) {
    int n = matrixRowSize;
    int a = 0;
    int b = n-1;
    while(a<b){
        for(int i=0;i<(b-a);++i){
            swap(&m4x4[a][a+i], &m4x4[a+i][b]);
            swap(&m4x4[a][a+i], &m4x4[b][b-i]);
            swap(&m4x4[a][a+i], &m4x4[b-i][a]);
        }
        ++a;
        --b;
    }
}

void print(){
    for (int i=0; i<16; i++){
      for (int j=0; j<16; j++)
        putchar(m4x4[i][j]);
      putchar('\n');
    }
}

int main(){
    print();
    rotate(16,16);
    printf("===========================\n");
    print();    
    return 0;
}













