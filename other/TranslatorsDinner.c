#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////////////
enum{ MAX_LANGUAGES   = 100};
enum{ MAX_TRANSLATORS = 200};

int N, M;
int languages   [MAX_TRANSLATORS][2];
int linearSystem[MAX_LANGUAGES][MAX_TRANSLATORS + 1];
int x           [MAX_TRANSLATORS];
int rowPivot    [MAX_LANGUAGES];
int colPivot    [MAX_TRANSLATORS];

int main() {
  scanf("%d %d", &N, &M);
  assert(N >= 2 && N <= MAX_LANGUAGES);
  assert(M >= 1 && M <= MAX_TRANSLATORS);
  for (int i = 0; i < N; i++) rowPivot[i] = -1;
  for (int j = 0; j < M; j++) colPivot[j] = -1;
  for (int j = 0; j < M; j++){
    int A, B;
    scanf("%d %d", &A, &B);
    assert(A >= 0 && A < N);
    assert(B >= 0 && B < N);
    languages[j][0] = A;
    languages[j][1] = B;
    linearSystem[A][j] = 1;
    linearSystem[B][j] = 1;
    linearSystem[A][M] ^= 1;
  }
  for(int curPivotCol = 0; curPivotCol < M; curPivotCol++){
    int curPivotRow = -1;
    for (int i = 0; i < N; i++){
      if (rowPivot[i] == -1 && linearSystem[i][curPivotCol] == 1){
        curPivotRow = i;
        break;
      }
    }
    if (curPivotRow == -1)
      continue;
    rowPivot[curPivotRow] = curPivotCol;
    colPivot[curPivotCol] = curPivotRow;
    for (int i = 0; i < N; i++) {
      if (i == curPivotRow)
        continue;
      if (linearSystem[i][curPivotCol] == 1) {
        for (int j = 0; j <= M; j++) {
          linearSystem[i][j] ^= linearSystem[curPivotRow][j];
        }
      }
    }
  }
  for (int j = 0; j < M; j++)
    x[j] = 0;
  for (int i = 0; i < N; i++){
    if (rowPivot[i] != -1){
      x[rowPivot[i]] = linearSystem[i][M];
    }
    else if (linearSystem[i][M] != 0) {
      puts("impossible");
      return 0;
    }
  }
  vec perLanguage[MAX_LANGUAGES]; memset(perLanguage, 0, sizeof(perLanguage));
  for(int j = 0; j < M; j++){
    perLanguage[languages[j][x[j]]].ptr = pushback(perLanguage[languages[j][x[j]]].ptr, &perLanguage[languages[j][x[j]]].sz, j);
  }
  for(int i = 0; i < N; i++){
    unsigned l = perLanguage[i].sz;
    assert(l % 2 == 0);
    for(unsigned j = 0; j < l; j += 2){
      printf("%d %d\n", perLanguage[i].ptr[j], perLanguage[i].ptr[j + 1]);
    }
  }
  return 0;
}
