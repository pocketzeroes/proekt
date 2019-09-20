#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first;
  int second;
}pair;

typedef struct{
  double first;
  char*  second;
}pds;
int cmpPds(const void*pa, const void*pb){
  pds*a = (pds*)pa;
  pds*b = (pds*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  return strcmp(a->second, b->second);
}

char line[200000];
char*getln(){
  gets(line);
  return strdup(line);
}

int main(){
    char*s = getln();
    char*t = getln();
    pair sb, sr, sd, tb, tr, td;
    if(strcmp(s, "Black")==0){
        sb =(pair){3, 1};
        sr =(pair){0, 1};
        sd =(pair){3, 1};
    }
    else if(strcmp(s, "Blue")==0){
        sb =(pair){3, 1};
        sr =(pair){0, 1};
        sd =(pair){0, 1};
    }
    else if(strcmp(s, "Chocolate")==0){
        sb =(pair){0, 1};
        sr =(pair){0, 1};
        sd =(pair){3, 1};
    }
    else if(strcmp(s, "Lilac")==0){
        sb =(pair){0, 1};
        sr =(pair){0, 1};
        sd =(pair){0, 1};
    }
    else if(strcmp(s, "Red")==0){
        sb =(pair){1, 1};
        sr =(pair){1, 0};
        sd =(pair){3, 1};
    }
    else if(strcmp(s, "Cream")==0){
        sb =(pair){1, 1};
        sr =(pair){1, 0};
        sd =(pair){0, 1};
    }
    else if(strcmp(s, "Black-Red Tortie")==0){
        sb =(pair){3, 1};
        sr =(pair){1, 1};
        sd =(pair){3, 1};
    }
    else if(strcmp(s, "Blue-Cream Tortie")==0){
        sb =(pair){3, 1};
        sr =(pair){1, 1};
        sd =(pair){0, 1};
    }
    else if(strcmp(s, "Chocolate-Red Tortie")==0){
        sb =(pair){0, 1};
        sr =(pair){1, 1};
        sd =(pair){3, 1};
    }
    else{
        sb =(pair){0, 1};
        sr =(pair){1, 1};
        sd =(pair){0, 1};
    }
    if(strcmp(t, "Black")==0){
        tb =(pair){3, 1};
        tr =(pair){0, 1};
        td =(pair){3, 1};
    }
    else if(strcmp(t, "Blue")==0){
        tb =(pair){3, 1};
        tr =(pair){0, 1};
        td =(pair){0, 1};
    }
    else if(strcmp(t, "Chocolate")==0){
        tb =(pair){0, 1};
        tr =(pair){0, 1};
        td =(pair){3, 1};
    }
    else if(strcmp(t, "Lilac")==0){
        tb =(pair){0, 1};
        tr =(pair){0, 1};
        td =(pair){0, 1};
    }
    else if(strcmp(t, "Red")==0){
        tb =(pair){1, 1};
        tr =(pair){1, 0};
        td =(pair){3, 1};
    }
    else{
        tb =(pair){1, 1};
        tr =(pair){1, 0};
        td =(pair){0, 1};
    }
    double x[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double q = (sb.first + sb.second) *
               (sr.first + sr.second) *
               (sd.first + sd.second) *
               (tb.first + tb.second) *
               (tr.first + tr.second) *
               (td.first + td.second);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                for (int l = 0; l < 2; l++)
                    for (int m = 0; m < 2; m++)
                        for (int n = 0; n < 2; n++){
                            int p = (i ? sb.second : sb.first) * (j ? sr.second : sr.first) *
                                (k ? sd.second : sd.first) * (l ? tb.second : tb.first) *
                                (m ? tr.second : tr.first) * (n ? td.second : td.first);
                            if (!p)
                                continue;
                            if ((i == 0 || l == 0) && j == 1 && m == 1 && (k == 0 || n == 0)) x[0] += p / q;
                            else if ((i == 0 || l == 0) && j == 1 && m == 1 && k == 1 && n == 1) x[1] += p / q;
                            else if (i == 1 && l == 1 && j == 1 && m == 1 && (k == 0 || n == 0)) x[2] += p / q;
                            else if (i == 1 && l == 1 && j == 1 && m == 1 && k == 1 && n == 1) x[3] += p / q;
                            else if (j == 0 && m == 0 && (k == 0 || n == 0)) x[4] += p / q;
                            else if (j == 0 && m == 0 && k == 1 && n == 1) x[5] += p / q;
                            else if ((i == 0 || l == 0) && j == 1 && m == 0 && (k == 0 || n == 0)) {
                                x[0] += p / (q * 2);
                                x[6] += p / (q * 2);
                            }
                            else if ((i == 0 || l == 0) && j == 1 && m == 0 && k == 1 && n == 1) {
                                x[1] += p / (q * 2);
                                x[7] += p / (q * 2);
                            }
                            else if (i == 1 && l == 1 && j == 1 && m == 0 && (k == 0 || n == 0)) {
                                x[2] += p / (q * 2);
                                x[8] += p / (q * 2);
                            }
                            else if (i == 1 && l == 1 && j == 1 && m == 0 && k == 1 && n == 1) {
                                x[3] += p / (q * 2);
                                x[9] += p / (q * 2);
                            }
                            else if ((i == 0 || l == 0) && j == 0 && m == 1 && (k == 0 || n == 0)) {
                                x[4] += p / (q * 2);
                                x[6] += p / (q * 2);
                            }
                            else if ((i == 0 || l == 0) && j == 0 && m == 1 && k == 1 && n == 1) {
                                x[5] += p / (q * 2);
                                x[7] += p / (q * 2);
                            }
                            else if (i == 1 && l == 1 && j == 0 && m == 1 && (k == 0 || n == 0)) {
                                x[4] += p / (q * 2);
                                x[8] += p / (q * 2);
                            }
                            else if (i == 1 && l == 1 && j == 0 && m == 1 && k == 1 && n == 1) {
                                x[5] += p / (q * 2);
                                x[9] += p / (q * 2);
                            }
                        }
    char*n[10] = {"Black", "Blue", "Chocolate", "Lilac", "Red", "Cream", "Black-Red Tortie", "Blue-Cream Tortie", "Chocolate-Red Tortie", "Lilac-Cream Tortie"};
    pds v[10];
    int vsz = 0;
    for(int i=0; i<10; i++)
        if(x[i])
            v[vsz++]=(pds){-x[i], n[i]};
    qsort(v, vsz, sizeof(pds), cmpPds);
    for(int i=0;i<vsz;i++){pds z=v[i];
        printf("%s %.9lf\n", z.second, -z.first);
    }
    return 0;
}
