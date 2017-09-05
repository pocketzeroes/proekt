#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
////////////////////

enum{ kMaxN = 300005    };
enum{ mod   = 1000000007};
int N, S, A, B, C;
pair s[kMaxN];
int head;

int main(){
    scanf("%d %d %d %d %d", &N, &S, &A, &B, &C);
    if(A != 1){
  basic:
        head = 1;
        s[1] = newPair(S, 1);
        int ans = 0;
        for (int i = 2, curr = S; i <= N + 1; ++i){
            curr = (1LL * curr * A + B) % C;
            if(i == N + 1)
                curr = (1 << 30);
            while(head && s[head].first <= curr){
                ans = (ans + 1LL * (1LL * (s[head].second - s[head - 1].second) * (i - s[head].second) % mod) * s[head].first) % mod;
                head--;
            }
            s[++head] = newPair(curr, i);
        }
        printf("%d\n", ans);
    }
    else{
        head = 1;
        s[1] = newPair((S + 1LL * (N - 1) * B) % C, 1);
        int ans = 0;
        for (int i = 2, curr = (S + 1LL * (N - 1) * B) % C; i <= N + 1; ++i){
            curr = (1LL * curr - 1LL * B + 1LL * C) % C;
            if (i == N + 1)
                curr = (1 << 30);
            while (head && s[head].first <= curr){
                ans = (ans + 1LL * (1LL * (s[head].second - s[head - 1].second) * (i - s[head].second) % mod) * s[head].first) % mod;
                head--;
            }
            s[++head] = newPair(curr, i);
            if (head == 300000)
                goto basic;
        }
        printf("%d\n", ans);
    }
	return 0;
}























































