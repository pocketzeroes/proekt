int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
typedef struct {
}Leaderboard;
Leaderboard*gptr;
int scores[10010];

Leaderboard* leaderboardCreate() {
    memset(scores,0,sizeof(scores));
    return gptr;
}
void leaderboardAddScore(Leaderboard* obj, int playerId, int score) {
    scores[playerId] += score;
}
int leaderboardTop(Leaderboard* obj, int K) {
    int*brr = calloc(10010, sizeof(int));
    memcpy(brr, scores, sizeof(scores));
    qsort(brr, 10010, sizeof(int), cmp);
    int ans = 0;
    for(int i = 10010-1; i >= 10010-K; i--)
        ans += brr[i];
    return ans;
}
void leaderboardReset(Leaderboard* obj, int playerId) {
    scores[playerId] = 0;
}
void leaderboardFree(Leaderboard* obj) {
    ;
}
