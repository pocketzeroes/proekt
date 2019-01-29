#include <stdio.h>
typedef long double ld;

ld s[20];
ld p[20];
ld over_band;
ld e[20];
ld m[20];
ld g[20];

int main(){
  int b, ignore;
  ignore = scanf("%d", &b);
  for (int i=0; i<b; i++){
    ignore = scanf("%Lf %Lf", &s[i], &p[i]);
    p[i] = p[i] / 100;
  }
  ignore = scanf("%Lf", &over_band);
  over_band = over_band / 100;
  int f; 
  ignore = scanf("%d", &f);
  for(int j=0; j < f; j++){
    ignore = scanf("%Lf %Lf", &e[j], &m[j]);
    ld my_e = e[j];
    int k;
    ld t = 0;
    for(k = 0; k < b ; k++) {
      my_e -= s[k];
      if (my_e <= 0) {
        if (my_e + (m[j] / (1 - p[k])) < 0) {
          t += m[j] / (1 - p[k]);
          m[j] = 0;
          break;
        }
        else {
          t -= my_e; 
          m[j] += -my_e * p[k];
          m[j] += my_e; 
          my_e = 0; 
        }
      }  
    }
    if (m[j] > 0) {
      t += m[j] / (1 - over_band);
    }
    printf("%.7Lf\n", t);
  }
  return 0;
}
