#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 4005};

    int numOfPoints, numOfAntennas, height, weight;
    int graph[MAXN][MAXN], number[MAXN][MAXN];
    bool visited[MAXN];
    int pairs[MAXN];
    bool findpath(int);
    void hungray();
    void init();
    void input();
    void output();

void init() {
    memset(graph, 0, sizeof(graph));
    memset(number, 0, sizeof(number));
    memset(pairs, 0, sizeof(pairs));
    numOfPoints = 0;
    numOfAntennas = 0;
}
void input() {
    scanf("%d%d", &height, &weight);

    int cnt = 0;
    getchar();
    for (int i = 0; i < height; i++) {
        for(int j = 0; j < weight; j++) {
            char s=getchar();
            if (s == '*') {
                cnt++;
                number[i][j] = cnt;
            }
        }
        getchar();
    }
    numOfPoints = cnt;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < weight; j++) {
            if (number[i][j] != 0) {
                if (i > 0 && number[i - 1][j] != 0)
                    graph[number[i][j]][number[i - 1][j]] = 1;
                if (i < height - 1 && number[i + 1][j] != 0)
                    graph[number[i][j]][number[i + 1][j]] = 1;
                if (j > 0 && number[i][j - 1] != 0)
                    graph[number[i][j]][number[i][j - 1]] = 1;
                if (j < weight - 1 && number[i][j + 1] != 0)
                    graph[number[i][j]][number[i][j + 1]] = 1;
            }
        }
    }
}
bool findpath(int x) {
    for (int y = 1; y <= numOfPoints; y++) {
        if (graph[x][y] && !visited[y]) {
            visited[y] = true;
            if (pairs[y] == 0 || findpath(pairs[y])) {
                pairs[y] = x;
                return true;
            }
        }
    }
    return false;
}
void hungray() {
    int match = 0;
    for (int i = 1; i <= numOfPoints; i++) {
        memset(visited, false, sizeof(visited));
        if (findpath(i)) {
            match++;
        }
    }
    numOfAntennas = numOfPoints - match / 2;
}
void output() {
    printf("%d\n", numOfAntennas);
}

int main() {
    int nCase;
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        hungray();
        output();
    }
    return 0;
}
