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

typedef long long ll;

int grid[10][10];
bool br;
pair goTo    [1100][1100];
pair trueGoTo[1100][1100];
int answer   [1100][1100];


void tr(int x, int y, int depth){
    if (br)
        return;
    if (x == 1 && y == 1 && depth == 26) {
        br = true;
    }
    if (br)
        return;
    if (x < 1 || x>5)
        return;
    if (y < 1 || y>5)
        return;
    if (grid[x][y] != 0)
        return;
    grid[x][y] = depth;
    tr(x + 3, y, depth + 1);
    tr(x - 3, y, depth + 1);
    tr(x, y+3, depth + 1);
    tr(x, y-3, depth + 1);
    tr(x+2, y +2, depth + 1);
    tr(x + 2, y - 2, depth + 1);
    tr(x - 2, y + 2, depth + 1);
    tr(x - 2, y - 2, depth + 1);
    if (br)
        return;
    grid[x][y] = 0;
}
void rev(int a, int b){
    pair newGoTo[5][5];
    for(int i = 0; i<(5); i++)for(int j = 0; j<(5); j++) {
        int x = a + i;
        int y = b + j;
        trueGoTo[goTo[x][y].first][goTo[x][y].second] = newPair(x, y);
    }
}
void getAns(pair cur, int depth){
    if(answer[cur.first][cur.second])
        return;
    answer[cur.first][cur.second] = depth;
    getAns(goTo[cur.first][cur.second], depth + 1);
}
int main(){
    tr(1, 1, 1);
    for(int i = 0; i<(5); i++)for(int j = 0; j<(5); j++)for(int k = 0; k<(5); k++)for(int l = 0; l<(5); l++) {
        if (grid[i+1][j+1] - 1 == grid[k+1][l+1] || grid[i+1][j+1] == 1 && grid[k+1][l+1] == 25)
            goTo[k][l] = newPair(i, j);
    }
    int N; 
    scanf("%d", &N);
    for(int i = 0; i<(N); i++)for(int j = 0; j<(N); j++) {
        goTo[i][j] = goTo[i % 5][j % 5];
        goTo[i][j].first  += i - i % 5;
        goTo[i][j].second += j - j % 5;
    }
    for (int i = 0; i < N-5; i += 5) {
        goTo[i + 4][3] = newPair(i + 7, 3);
        goTo[i + 7][0] = newPair(i + 4, 0);
    }
    for(int i = 0;i<N;i += 5)
        for (int j = 0; j < N - 5; j += 5) {
           goTo[i + 1][j + 3] = newPair(i + 1, j + 6);
           goTo[i + 4][j + 6] = newPair(i + 4, j + 3);
        }
    getAns(newPair(0,0),1);
    for(int i = 0; i<(N); i++) {
        for(int j = 0; j<(N); j++)
            printf("%d ", answer[i][j]);
        puts("");
    }
    return 0;
}























































