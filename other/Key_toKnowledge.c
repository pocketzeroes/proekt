#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
  ll  first;
  int second;
}pair;
pair newPair(ll a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
//////////////////////
enum{ nmax = 12};
enum{ mmax = 30};

int StudentAnswers[nmax], 
    StudentScore  [nmax];

pair Scores1[1<<(mmax/2)], 
     Scores2[1<<(mmax-mmax/2)];

int score(int m, int solution, int answers){
    return m - __builtin_popcount(solution ^ answers);
}
int main(){
    int runs, run, n, m, a, a1, a2, i, j, k1, k2, m1, m2, nsol, solution;
    ll s, s1, s2, target;
    char c;
    scanf("%d", &runs);
    for (run = 0; run < runs; run++){
        scanf("%d %d ", &n, &m);
        for (i = 0; i < n; i++){
            a = 0;
            for (j = 0; j < m; j++){
                scanf("%c", &c);
                a = 2*a + (c-'0');
            }
            StudentAnswers[i] = a;
            scanf("%d ", &StudentScore[i]);
        }
        target = 0;
        for (i = 0; i < n; i++)
            target |= (((ll)StudentScore[i]) << (5*i));
        m1 = m/2;
        m2 = m-m1;
        for (a1 = 0; a1 < (1<<m1); a1++){
            s1 = 0;
            for (i = 0; i < n; i++)
                s1 |= ((ll)(score(m1, a1, StudentAnswers[i] >> m2))) << (5*i);
            Scores1[a1] = newPair(s1, a1);
        }
        for (a2 = 0; a2 < (1<<m2); a2++){
            s2 = 0;
            for (i = 0; i < n; i++)
                s2 |= ((ll)(score(m2, a2, StudentAnswers[i] & ((1<<m2)-1)))) << (5*i);
            Scores2[a2] = newPair(s2, a2);
        }
        qsort(Scores1, (1<<m1), sizeof(pair), cmpP);
        qsort(Scores2, (1<<m2), sizeof(pair), cmpP);
        nsol = solution = 0;
        i = 0;
        j = (1<<m2)-1;
        while (i < (1<<m1) && j >= 0){
            s = Scores1[i].first + Scores2[j].first;
            if (s == target){
                solution = ((Scores1[i].second << m2) | Scores2[j].second);
                k1 = k2 = 1;
                for (i++; i < (1<<m1) && Scores1[i].first == Scores1[i-1].first; i++, k1++);
                for (j--; j >= 0 && Scores2[j].first == Scores2[j+1].first; j--, k2++);
                nsol += k1*k2;
            }
            else if (s < target)
                i++;
            else
                j--;
        }
        if (nsol == 1){
            for (j = m-1; j >= 0; j--)
                printf("%d", !!(solution & (1<<j)));
            printf("\n");
        }
        else
            printf("%d solutions\n", nsol);
    }
    return 0;
}
