#include<stdio.h>

int main(){
  int N, B, H, W;
  scanf("%d %d %d %d", &N, &B, &H, &W);
  int minimum = B + 1;
  for (int h = 0; h < H; ++h){
    int p;
    scanf("%d", &p);  
    for (int w = 0; w < W; ++w){
      int a; 
      scanf("%d", &a); 
      if (a >= N && N * p < minimum)
        minimum = N * p;
    }
  }
  if (minimum <= B) 
    printf("%d\n", minimum);
  else
    printf("stay home\n");
}
