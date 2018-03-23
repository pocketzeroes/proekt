#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ NUM_SUSPECTS = 26};
int**coeffs;
int rows;
enum { NUM_COLS = 1 + 2*NUM_SUSPECTS};

typedef struct{
    int suspect1;
    int suspect2;
    int player;
    int count;
}Constr;
Constr*constraints;
int    constraints_length;

Constr newConstr(char*str, int player, int count){
    Constr rez;
//  if(strlen(str) != 2 || player < 0 || player > 1 || count< 0 || count>2 ) fprintf(stderr, "Illegal Argument Exception");
    rez.suspect1 = str[0] - 'A';
    rez.suspect2 = str[1] - 'A';
    rez.player   = player;
    rez.count    = count;
    return rez;
}

void xorRows(int i, int k, int j);
bool impossible(int i);

int varix(int x, int p){
    return 2*x + p;
}
void addRow2(int i, int c){
    coeffs[rows][i] = 1;
    coeffs[rows][NUM_COLS-1] = c;
    rows ++;
}
void addRow(int i, int j, int c){
    coeffs[rows][i] = 1;
    coeffs[rows][j] = 1;
    coeffs[rows][NUM_COLS-1] = c;
    rows ++;
}
void makeSystem(int bv1, int bv2, int bv3){
    coeffs = calloc(2*(NUM_SUSPECTS+constraints_length), sizeof(int*));
    for(int z=0; z<2*(NUM_SUSPECTS+constraints_length); z++)
        coeffs[z] = calloc(NUM_COLS, sizeof(int));
    rows = 0;
    for(int x=0; x<NUM_SUSPECTS; x++){
        if(x==bv1 || x==bv2 || x==bv3){
            addRow2(varix(x,0), 0);
            addRow2(varix(x,1), 0);
        }
        else{
            addRow(varix(x,0), varix(x,1), 1);
        }
    }
    for(int i = 0; i<constraints_length; i++){
        Constr c = constraints[i];
        int x1 = c.suspect1;
        int x2 = c.suspect2;
        int p = c.player;
        switch(c.count) {
          case 0:
            addRow2(varix(x1,p), 0);
            addRow2(varix(x2,p), 0);
            break;
          case 2:
            addRow2(varix(x1,p), 1);
            addRow2(varix(x2,p), 1);
            break;
          case 1:
            addRow(varix(x1,p), varix(x2,p), 1);
            break;
          default:
            fprintf(stderr, "Illegal Argument Exception");
        }
    }
}
bool satisfiable(){
    int i=0, j=0;
    while (i<rows && j<NUM_COLS-1) {
        int pivot = i;
        while (pivot < rows && coeffs[pivot][j] == 0)
            pivot++;
        if (pivot < rows) {
            int tmp[NUM_COLS];
            memcpy(tmp,           coeffs[pivot], sizeof(tmp));
            memcpy(coeffs[pivot], coeffs[i],     sizeof(tmp));
            memcpy(coeffs[i],     tmp,           sizeof(tmp));
        }
        else {
            j++;
            continue;
        }
        for(int k=i+1; k<rows; k++) {
            if (coeffs[k][j] > 0)
                xorRows(i, k, j);
        }
        j++;
        i++;
    }
    int count10 = 0, count11 = 0;
    for(int k=i; k<rows; k++) {
        if (impossible(k))
            return false;
        if(coeffs[k][NUM_COLS-2] == 1 && coeffs[j][NUM_COLS-1] == 0)
            count10 ++;
        if(coeffs[k][NUM_COLS-2] == 1 && coeffs[j][NUM_COLS-1] == 1)
            count11 ++;
    }
    return !(count10>0 && count11>0);
}
bool impossible(int i){
    for (int j=0; j<NUM_COLS-1; j++)
        if (coeffs[i][j] != 0)
            return false;
    return coeffs[i][NUM_COLS-1] == 1;
}
void xorRows(int i, int k, int j){
    while(j < NUM_COLS){
        coeffs[k][j] ^= coeffs[i][j];
        j++;
    }
}
int solve(){
    int solutions = 0;
    for(int x = 0; x<NUM_SUSPECTS; x++)
        for(int y=x+1; y<NUM_SUSPECTS; y++)
            for(int z=y+1; z<NUM_SUSPECTS; z++){
                makeSystem(x, y, z);
                if(satisfiable())
                    solutions++;
            }
    return solutions;
}
char buff[1000];
void readInput(){
    int n;
    scanf("%d", &n);
    constraints = calloc(n, sizeof(Constr));
    constraints_length = n;
    for(int i=0; i<n; i++){
        char*str;
        scanf("%s", &buff);
        str = strdup(buff);
        int player;
        scanf("%d", &player); player--;
        int count;
        scanf("%d", &count);
        constraints[i] = newConstr(str, player, count);
        free(str);
    }
}
int main(int argc, char**argv){
    readInput();
    int rv = solve();

    printf("%d\n", rv);
    return 0;
}



