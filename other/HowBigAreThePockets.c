#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define newpt __builtin_complex
typedef long long ll;
typedef complex double pt;

typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
//////////////////////////
pair row_rng_s[7100];
pair * row_rng = row_rng_s + 3050;
pair col_rng_s[7100];
pair * col_rng = col_rng_s + 3050;

pt del[4] = {
    newpt(1., 0.),
    newpt(0., 1.),
    newpt(-1., 0.),
    newpt(0., -1.)
};

int main(){
    int cases;
    scanf("%d", &cases);
    for (int cas = 0; cas < cases; cas++){
        int L;
        scanf("%d", &L);
        char s[64];
        int T;
        pt cur = newpt(0., 0.);
        int head = 0;
        ll area = 0;
        for(int i = -3001; i <= 3001; i++){
            col_rng[i] = newpair(INT_MAX, INT_MIN);
            row_rng[i] = newpair(INT_MAX, INT_MIN);
        }
        for(int i = 0; i < L; i++){
            scanf("%s %d", &s, &T);
            int len = strlen(s);
            for(int rep = 0; rep < T; rep++){
                for(int j = 0; j < len; j++){
                    switch(s[j]){
                      case 'L':
                        head = (head + 1) & 3;
                        break;
                      case 'R':
                        head = (head - 1) & 3;
                        break;
                      case 'F':{
                            pt nxt = cur + del[head];
                            int idx;
                            switch (head){
                              case 0:
                              case 2:
                                idx = fmin(creal(cur), creal(nxt));
                                col_rng[idx].first  = fmin(col_rng[idx].first,  cimag(cur));
                                col_rng[idx].second = fmax(col_rng[idx].second, cimag(cur));
                                break;
                              case 1:
                              case 3:
                                idx = fmin(cimag(cur), cimag(nxt));
                                row_rng[idx].first  = fmin(row_rng[idx].first,  creal(cur));
                                row_rng[idx].second = fmax(row_rng[idx].second, creal(cur));
                                break;
                            }
                            area += cimag(conj(cur)*nxt);
                            cur = nxt;
                        }
                    }
                }
            }
        }
        assert(cur == newpt(0., 0.));
        int ans = 0;
        for(int i = -3001; i <= 3001; i++)
            for(int j = -3001; j <= 3001; j++)
                if ((j >= row_rng[i].first && j < row_rng[i].second) ||
                    (i >= col_rng[j].first && i < col_rng[j].second)  )
                    ans++;
        ans -= llabs(area / 2);
        printf("Case #%d: %d\n", cas + 1, ans);
    }
    return 0;
}
