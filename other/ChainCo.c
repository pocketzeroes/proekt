#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct{
    int c[3][2];
}box;

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
box*pushbackB(box*array, int *size, box value){
  box*output = resizeArray(array, box, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	box*ptr;
	int sz;
}vecb;
vecb newVecB(){
	vecb rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////
vecb boxes[3];

bool run(int total){
    if (boxes[0].sz == 0 || boxes[0].sz == total)
        return false;
    vecb*bx = &boxes[0];
    vecb*by = &boxes[1];
    box B = (box){INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX};
    for (int i = 0; i < bx->sz; ++i) {
        box b = bx->ptr[i];
        int r = b.c[1][1] - b.c[1][0];
        b.c[0][0] -= r;
        b.c[2][0] -= r;
        for (int j = 0; j < 3; ++j){
            B.c[j][0] = max(B.c[j][0], b.c[j][0]);
            B.c[j][1] = min(B.c[j][1], b.c[j][1]);
        }
    }
    for (int i = 0; i < by->sz; ++i)
        for (int j = 0; j < 3; ++j)
            if(by->ptr[i].c[j][0] <= B.c[j][0] || by->ptr[i].c[j][0] >= B.c[j][1])
                return false;
    return true;
}

void swap_c(int x, int y) {
    for (int k = 0; k < 3; ++k){
        for (int i = 0; i < boxes[k].sz; ++i){
            swap(boxes[k].ptr[i].c[x][0], boxes[k].ptr[i].c[y][0]);
            swap(boxes[k].ptr[i].c[x][1], boxes[k].ptr[i].c[y][1]);
        }
    }
    swap(boxes[x], boxes[y]);
}

void test_() {
    int total;
    scanf("%d", &total);
    for (int i = 0; i < 3; ++i)
        boxes[i].sz=0;
    for (int j = 0; j < total; ++j) {
        box b;
        scanf("%d%d%d", &b.c[0][0], &b.c[1][0], &b.c[2][0]);
        scanf("%d%d%d", &b.c[0][1], &b.c[1][1], &b.c[2][1]);
        for (int i = 0; i < 3; ++i) {
            int m = min(b.c[i][0], b.c[i][1]);
            int M = max(b.c[i][0], b.c[i][1]);
            b.c[i][0] = m;
            b.c[i][1] = M;
        }
        int cc = 0;
        if (b.c[1][0] == b.c[1][1]) cc = 1;
        else if (b.c[2][0] == b.c[2][1]) cc = 2;
        boxes[cc].ptr = pushbackB(boxes[cc].ptr, &boxes[cc].sz, b);
    }
    bool ok0 = run(total);
    swap_c(1, 2);
    bool ok1 = run(total);
    swap_c(0, 2);
    bool ok2 = run(total);
    swap_c(1, 2);
    bool ok3 = run(total);
    swap_c(0, 2);
    bool ok4 = run(total);
    swap_c(1, 2);
    bool ok5 = run(total);
    puts(ok0 && ok1 || ok2 && ok3 || ok4 && ok5 ? "YES" : "NO");
}

int main() {
    int c;
    scanf("%d", &c);
    while(c--)
        test_();
    return 0;
}
