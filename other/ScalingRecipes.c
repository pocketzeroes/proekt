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
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
double in_nextDouble(){
  double x;
  scanf("%lf", &x);
  return x;
}

int main(){
    int T = in_nextInt();
    for(int t = 1; t <= T; t++){
        int R = in_nextInt();
        int P = in_nextInt();
        int D = in_nextInt();
        printf("Recipe # %d\n", t);
        char*  name  [R];
        double weight[R];
        double perc  [R];
        double scale = (D * 1.0) / (P * 1.0);
        int mainIdx = -1;
        for(int j = 0; j < R; j++){
            name  [j] = getstr();
            weight[j] = in_nextDouble();
            perc  [j] = in_nextDouble();
            if(fabs(perc[j] - 100) < 0.005)
                mainIdx = j;
        }
        double scaleWeightMain = weight[mainIdx] * scale;
        for(int j = 0; j < R; j++){
            printf("%s", name[j]);
            printf(" ");
            printf("%lf\n", (perc[j] * scaleWeightMain) / 100.0);
        }
        for(int k = 0; k < 40; k++)
            printf("-");
        puts("");
    }
    return 0;
}
