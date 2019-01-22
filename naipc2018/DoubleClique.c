#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int deg[n]; memset(deg, 0, sizeof(deg));
    pair  e[m]; memset(  e, 0, sizeof(  e));
    for(int i=0; i<m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        if(a > b)
          swap(a, b);
        deg[a]++;
        deg[b]++;
        e[i] = newPair(a, b);
    }
    int inte[n]; memset(inte, 0, sizeof(inte));
    int intn[n]; memset(intn, 0, sizeof(intn));
    int hi = n-1;
    for(int i=0; i<m; i++){
        inte[min(deg[e[i].first], deg[e[i].second])]++;
        hi = min(hi, max(deg[e[i].first], deg[e[i].second]));
    }
    for(int i=0; i<n; i++)
        intn[deg[i]]++;
    for(int i=n-1; i>0; i--){
        intn[i-1] += intn[i];
        inte[i-1] += inte[i];
    }
    int r = 0;
    for(int ce=1; ce<=hi; ce++){
        int cs = intn[ce];
        int clique_edges = inte[ce];
        if(2 * clique_edges == cs * (cs - 1)){
            r = 1;
            for(int i=0; i<n; i++)
                if((deg[i] >= ce && deg[i] == cs-1) || (deg[i] < ce && deg[i] == cs))
                    r++;
            break;
        }
    }
    printf("%d\n", r);
    return 0;
}
