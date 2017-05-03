#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int Asize;
int A0size;

int largestSquare(int**A){
  int N = Asize;
  int up[N];
  int left[N];
  int square[N];
  int answer = 1;
  for(int j = 0; j < N; j++) {
    up[j] = 1;
    square[j] = 1;
  }
  for(int i = 1; i < N; i++) {
    left[0] = 1;
    for(int j = 1; j < N; j++) {
      if (A[i][j] == A[i][j - 1])
        left[j] = left[j - 1] + 1;
      else
        left[j] = 1;
      if (A[i][j] == A[i - 1][j])
        up[j]++;
      else
        up[j] = 1;
    }
    for(int j = N - 1; j >= 0; j--) {
      if (A[i][j] == A[i - 1][j - 1])
        square[j] = min(min(square[j - 1] + 1, left[j]), up[j]);
      else
        square[j] = 1;
      if (answer < square[j])
        answer = square[j];
    }
  }
  return answer;
}

int main() {
    int N;
    scanf("%d", &N);
    Asize =N;
    A0size=N;
    int**A=malloc(N*sizeof(int*));
    for(int i = 0; i < N; ++i)
        A[i]=malloc(N*sizeof(int));
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            scanf("%d", &A[i][j]);
        }
    }
    printf("%d", largestSquare(A) );
    return 0;
}
