#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

int max(int a,int b){return a>b?a:b;}

enum{ MAX_N   = 100};
enum{ MAX_K   = 26 };
enum{ MAX_LEN = 100};
int N, K;

int main() {
    scanf("%d %d", &N, &K);
    assert(1 <= N && N <= MAX_N);
    assert(1 <= K && K <= MAX_K);
    int best = -1;
    for (int i = 0; i < N; ++i) {
        char s[500];
        scanf("%s", &s);
        int letters[128];
        memset(letters, 0, sizeof(letters));
        int count = 0;
        for(int i=0;s[i];i++){char ch = s[i];
            if(letters[ch] == 0){
                ++count;
                letters[ch]++;
            }
        }
        if(count <= K) {
            best = max(best, strlen(s));
        }
    }
    printf("%d\n", best);
    return 0;
}
