#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXC = 1000,
   MAX_VAL = 1000000};
int R, C;
char in[3][MAXC+1], out[MAXC+1];

int eval(char arr[MAXC+1], int be, int en) {
    for (int i = en; i >= be; --i) {
        if (arr[i] == '+') {
            int v = eval(arr, be, i-1) + eval(arr, i+1, en);
            assert(-MAX_VAL <= v && v <= MAX_VAL);
            return v;
        }
        else if (arr[i] == '-') {
            int v = eval(arr, be, i-1) - eval(arr, i+1, en);
            assert(-MAX_VAL <= v && v <= MAX_VAL);
            return v;
        }
    }
    for (int i = be; i <= en; ++i) {
        if (arr[i] == '*') {
            int v = eval(arr, be, i-1) * eval(arr, i+1, en);
            assert(-MAX_VAL <= v && v <= MAX_VAL);
            return v;
        }
    }
    int n = 0;
    for (int i = be; i <= en; ++i)
        if (arr[i] != ' ')
            n = n * 10 + arr[i] - '0';
    assert(0 <= n && n <= MAX_VAL);
    return n;
}
int main(){
    while(1){
        scanf("%d%d", &R, &C);
        if (!R && !C)
            break;
        assert(1 <= R && R <= 3);
        assert(1 <= C && C <= MAXC);
        gets(in[0]);
        if (R == 1) {
            gets(in[1]);
            for (int c = 0; c < C; ++c)
                in[0][c] = in[2][c] = ' ';
        }
        else if (R == 2) {
            gets(in[0]);
            gets(in[1]);
            for (int c = 0; c < C; ++c)
                in[2][c] = ' ';
        }
        else {
            gets(in[0]);
            gets(in[1]);
            gets(in[2]);
        }
        int C2 = 0;
        for (int c = 0; c < C; ) {
            if (in[1][c] == '=') {
                int be = c, en = be;
                while (en < C && in[1][en] == '=') ++en;
                int den = eval(in[0], be, en-1),
                    nom = eval(in[2], be, en-1);
                assert(den % nom == 0);
                C2 += sprintf(out+C2, "%d", den / nom);
                c = en;
            }
            else if (in[1][c] == '\\') {
                int be = c+2, en = be;
                while (en < C && in[0][en] == '_') ++en;
                int sq = eval(in[1], be, en-1),
                    v = (int)(sqrt((double)sq)+0.5);
                assert(v*v == sq);
                C2 += sprintf(out+C2, "%d", v);
                c = en;
            }
            else {
                out[C2++] = in[1][c++];
            }
        }
        printf("%d\n", eval(out, 0, C2-1));
        break;
    }
    return 0;
}
