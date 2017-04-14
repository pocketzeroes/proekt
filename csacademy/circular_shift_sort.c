#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}



enum{ MAXN = 300};
int n, m, a[MAXN][MAXN];
int temp[MAXN];
pair where[MAXN*MAXN];//int sz[MAXN*MAXN];
typedef struct OperationS{
    char type;
    int index;
    int shift;
}Operation;
Operation newOperation(char _type, int _index, int _shift){
    Operation rez;
    rez.type  = _type ;
    rez.index = _index; 
    rez.shift = _shift;
    return rez;
}
Operation*solution=NULL;int solutionSz=0;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Operation*pushbackO(Operation*array, int *size, Operation value){
    Operation*output = resizeArray(array, Operation, *size + 1);
    output[(*size)++] = value;
    return output;
}



int Modulo(int x, int n){
    if (x < 0)  x += n;
    if (x >= n) x -= n;
    return x;
}
void MakeMove(bool line, int index, int shift) {
    if (!shift)
        return;
    if (line) {
        for (int i = 0; i < m; i++)
            temp[i] = a[index][i];
        for (int i = 0; i < m; i++) {
            a[index][i] = temp[Modulo(i - shift, m)];
            where[a[index][i]] = newPair(index, i);
        }
        solution=pushbackO(solution, &solutionSz, newOperation('R', index, shift));
    }
    else {
        for (int i = 0; i < n; i++)
            temp[i] = a[i][index];
        for (int i = 0; i < n; i++) {
            a[i][index] = temp[Modulo(i - shift, n)];
            where[a[i][index]] = newPair(i, index);
        }
        solution=pushbackO(solution, &solutionSz, newOperation('C', index, shift));
    }
}
int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            where[a[i][j]] = newPair(i, j);
        }
    }
    for (int i = 0; i <= n - 2; i++){
        for (int j = 0; j < m; j++) {
            int line = where[i * m + j].first, column = where[i * m + j].second;
            if (line != i && column != j) {
                MakeMove(false, j, line - i);
                MakeMove(true, line, j - column);
                MakeMove(false, j, i - line);
            }
            else{
                if (line != i) {
                    MakeMove(true, line, 1);
                    MakeMove(false, j, line - i);
                    MakeMove(true, line, -1);
                    MakeMove(false, j, i - line);
                }
                else{
                    if (column != j) {
                        MakeMove(true, i, j - column);
                        MakeMove(false, j, -1);
                        MakeMove(true, i, column - j);
                        MakeMove(false, j, 1);
                    }
                }
            }
        }
    }
    int sign = -1;
    for (int j = m - 1; j >= 0; j--) {
        int column = j;
        for (int i = 0; i <= j; i++){
            if (a[n - 1][i] == (n - 1) * m + j) {
                column = i;
                break;
            }
        }
        if (column == j)
            continue;
        MakeMove(true, n - 1, -column);
        MakeMove(false, 0, sign);
        sign *= -1;
        MakeMove(true, n - 1, column - j);
        MakeMove(false, 0, sign);
        sign *= -1;
        for (int i = column; i <= j - 1; i++) {
            MakeMove(true, n - 1, 1);
            MakeMove(false, 0, sign);
            sign *= -1;
        }
        MakeMove(true, n - 1, column);
    }
    bool ok = true;
    for (int i = 0; i <= n - 1; i++){
        if (a[i][0] != i * m) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        if (n % 2 && m % 2) {
            puts("-1");
            return 0;
        }
        sign = 1;
        MakeMove(true, 0, sign);
        sign *= -1;
        for (int i = 0; i <= n - 3; i++) {
            MakeMove(false, 0, -1);
            MakeMove(true, 0, sign);
            sign *= -1;
        }
        MakeMove(false, 0, -2);
        MakeMove(true, 0, sign);
        sign *= -1;
        if (n % 2) {
            sign = 1;
            MakeMove(false ,1, sign);
            sign *= -1;
            MakeMove(true, 0, 2 - m);
            for (int i = 0; i <= m - 3; i++) {
                MakeMove(false, 1, sign);
                sign *= -1;
                MakeMove(true, 0, 1);
            }
            MakeMove(false, 1, sign);
            sign *= -1;
        }
    }
    for(int i=0;i<solutionSz;i++){
        Operation it = solution[i];
        printf("%c %d %d\n", it.type, it.index, it.shift);
    }
    return 0;
}






























































