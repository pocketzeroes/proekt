#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int N;
bool *out;
int *nxt, *prv;
int *ans;



void removeIt(int nr) {
    out[nr] = true;
    nxt[prv[nr]] = nxt[nr];
    prv[nxt[nr]] = prv[nr];
}
void readd(int nr) {
    out[nr] = false;
    nxt[prv[nr]] = nr;
    prv[nxt[nr]] = nr;
}
void backtr(int pos, int maximum, int rem) {
    if (pos == N + 1) {
        for (int i = 1; i <= N; ++ i)
            printf("%d%c", ans[i], " \n"[i == N]);
        return ;
    }
    if (N - pos + 1 == rem) {
        for (int i = nxt[0]; i <= maximum; i = nxt[i]) {
            ans[pos] = i;
            removeIt(i);
            backtr(pos + 1, maximum, rem - 1);
            readd(i);
        }
    }
    else {
        for (int i = 1; i <= maximum; ++ i) {
            ans[pos] = i;
            if (out[i])
                backtr(pos + 1, maximum, rem);
            else {
                removeIt(i);
                backtr(pos + 1, maximum, rem - 1);
                readd(i);
            }
        }
        for (int i = maximum + 1; i <= N; ++ i)
            if (rem + i - maximum <= N - pos + 1) {
                ans[pos] = i;
                removeIt(i);
                backtr(pos + 1, i, rem + i - maximum - 1);
                readd(i);
            }
            else
                break;
    }
}
void noGapsArrays(int _N) {
    N = _N;
    out = malloc(sizeof(bool)*(N + 1));
    nxt = malloc(sizeof(int )*(N + 1));
    prv = malloc(sizeof(int )*(N + 1));
    ans = malloc(sizeof(int )*(N + 1));
    for (int i = 1; i <= N; ++ i)
        out[i] = false, nxt[i] = i + 1, prv[i] = i - 1;
    backtr(1, 0, 0);
}
int main() {
    int N;
    scanf("%d", &N);
    noGapsArrays(N);
}

























