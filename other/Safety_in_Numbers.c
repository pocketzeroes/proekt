#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int accumulate(int*arr, int sz){
  int sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}
int main(){
    int cases;
    scanf("%d", &cases);
    for(int cas=0; cas<cases; cas++){
        int N;
        scanf("%d", &N);
        int J[N];
        for(int i=0; i<N; i++)
            scanf("%d", &J[i]);
        int X = accumulate(J, N);
        printf("Case #%d:", cas + 1);
        for (int i = 0; i < N; i++){
            double L = 0.0;
            double R = 1.0;
            while (R - L > 1e-9){
                double Yi = (L + R) / 2.0;
                double M = Yi;
                double score = J[i] + X * Yi;
                double Yt = Yi;
                for (int j = 0; j < N; j++){
                    if (j != i){
                        double y = (score - J[j]) / X;
                        if (y > 1.0)
                            goto safe;
                        if (y < 0.0)
                            y = 0.0;
                        Yt += y;
                    }
                }
                if (Yt > 1.0)
                    goto safe;
                L = M;
                continue;
    safe:       R = M;
            }
            printf(" %.6f", L * 100);
        }
        puts("");
    }
    return 0;
}
