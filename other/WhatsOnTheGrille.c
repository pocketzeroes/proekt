#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

enum{ MAXS = 50};

char grille[MAXS][MAXS];
int  order [MAXS* MAXS];

void rotateGrille(int size){
    char tmp[MAXS][MAXS];
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            tmp[i][j] = grille[i][j];
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            grille[j][size-i-1] = tmp[i][j];
}
bool buildOrder(int size){
    for(int i=0; i<size*size; i++)
        order[i] = -1;
    int k=0;
    for(int r=0; r<4; r++) {
        for(int i=0; i<size; i++)
            for(int j=0; j<size; j++)
                if (grille[i][j] == '.')
                    order[i*size + j] = k++;
        rotateGrille(size);
    }
    for(int i=0; i<size*size; i++)
        if(order[i] == -1)
            return false;
    return true;
}
int main(){
    int n;
    char*cipher;
    scanf("%d", &n);
    int gsize = 0;
    getchar();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grille[i][j] = getchar();
            if (grille[i][j] == '.')
                gsize++;
        }
        getchar();
    }
    cipher = getstr();
    int cipher_len=strlen(cipher);
    if (gsize*4 == n*n && buildOrder(n)){
        char*plain = strdup("");
        for(int i=0; i<cipher_len; i+=n*n){
            for(int j=0; j<n*n; j++)
                plain = concatc(plain, cipher[i+order[j]]);
        }
        puts(plain);
    }
    else
        puts("invalid grille");
    return 0;
}
