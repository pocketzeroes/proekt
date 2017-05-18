#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef char* string;
typedef string* VS;
char digit[7][10][5] = {
{".XX.","....",".XX.",".XX.","....",".XX.",".XX.",".XX.",".XX.",".XX."},
{"X..X","...X","...X","...X","X..X","X...","X...","...X","X..X","X..X"},
{"X..X","...X","...X","...X","X..X","X...","X...","...X","X..X","X..X"},
{"....","....",".XX.",".XX.",".XX.",".XX.",".XX.","....",".XX.",".XX."},
{"X..X","...X","X...","...X","...X","...X","X..X","...X","X..X","...X"},
{"X..X","...X","X...","...X","...X","...X","X..X","...X","X..X","...X"},
{".XX.","....",".XX.",".XX.","....",".XX.",".XX.","....",".XX.",".XX."}
};
char display[7][22] = {
".??...??.....??...??.",
"?..?.?..?...?..?.?..?",
"?..?.?..?.?.?..?.?..?",
".??...??.....??...??.",
"?..?.?..?.?.?..?.?..?",
"?..?.?..?...?..?.?..?",
".??...??.....??...??."
};

void WriteDigit(int x, int dig, char*** display)
{
    for (int y = 0; y < 7; y++)
        for (int i = 0; i < 4; i++)
            (*display)[y][x + i] = digit[y][dig][i];
}
char** GetDisplay(int time)
{
    char**ret=malloc(7*sizeof(char*));
    for(int i=0;i<7;i++){
        ret[i]=malloc(21);
        memset(ret[i],'.', 21);
    }
    ret[2][10] = ret[4][10] = 'X';
    if (time >= 10 * 60)
        WriteDigit(0, time / 10 / 60, &ret);
    WriteDigit(5, (time / 60) % 10, &ret);
    WriteDigit(12, ((time % 60) / 10) % 10, &ret);
    WriteDigit(17, time % 10, &ret);
    return ret;
}
char buff[10000];
int main()
{
    int N;
    scanf("%d", &N);
    do{
        string d[N][7];
        for (int i = 0; i < N; i++)
            for (int y = 0; y < 7; y++){
                scanf("%s", &buff);
                d[i][y]=strdup(buff);
            }
        char* ret[7];
        for (int y = 0; y < 7; y++)
            ret[y] = strdup(display[y]);
        for (int i = 1; i < N; i++)
            for (int y = 0; y < 7; y++)
                for (int x = 0; x < 21; x++)
                    if (d[i - 1][y][x] != d[i][y][x])
                        ret[y][x] = 'W';
        for (int y = 0; y < 7; y++)
            for (int x = 0; x < 21; x++)
                if (ret[y][x] == '?')
                    ret[y][x] = (d[0][y][x] == 'X') ? '1' : '0';
        bool valid = false;
        for (int stime = 0; stime < 24 * 60; stime++) {
            char** displays[N];
            for (int i = 0; i < N; i++) {
                displays[i] = GetDisplay((stime + i) % (24 * 60));
                for (int y = 0; y < 7; y++)
                    for (int x = 0; x < 21; x++)
                        if (ret[y][x] == 'W' && displays[i][y][x] != d[i][y][x])
                            goto fail;
            }
            valid = true;
            for (int y = 0; y < 7; y++)
                for (int x = 0; x < 21; x++)
                    if (ret[y][x] == '0' || ret[y][x] == '1') {
                        int i;
                        for (i = 0; i < N; i++) {
                            if (ret[y][x] == '0' && displays[i][y][x] == 'X')
                                break;
                            if (ret[y][x] == '1' && displays[i][y][x] == '.')
                                break;
                        }
                        if (i == N)
                            ret[y][x] = '?';
                    }
    fail:;
        }
        if (!valid)
            puts("impossible");
        else {
            for (int y = 0; y < 7; y++)
                printf("%s\n", ret[y]);
        }
    }while(0);
}

















