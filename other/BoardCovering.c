#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#ifndef _CEXCEPTION_H
#define _CEXCEPTION_H
#include <setjmp.h>

#define CEXCEPTION_VERSION_MAJOR    1
#define CEXCEPTION_VERSION_MINOR    3
#define CEXCEPTION_VERSION_BUILD    2
#define CEXCEPTION_VERSION          ((CEXCEPTION_VERSION_MAJOR << 16) | (CEXCEPTION_VERSION_MINOR << 8) | CEXCEPTION_VERSION_BUILD)
#ifdef CEXCEPTION_USE_CONFIG_FILE
#include "CExceptionConfig.h"
#endif
#ifndef CEXCEPTION_NONE
#define CEXCEPTION_NONE      (0x5A5A5A5A)
#endif
#ifndef CEXCEPTION_NUM_ID
#define CEXCEPTION_NUM_ID    (1)
#endif
#ifndef CEXCEPTION_GET_ID
#define CEXCEPTION_GET_ID    (0)
#endif
#ifndef CEXCEPTION_T
#define CEXCEPTION_T         unsigned int
#endif
#ifndef CEXCEPTION_NO_CATCH_HANDLER
#define CEXCEPTION_NO_CATCH_HANDLER(id)
#endif
#ifndef CEXCEPTION_HOOK_START_TRY
#define CEXCEPTION_HOOK_START_TRY
#endif
#ifndef CEXCEPTION_HOOK_HAPPY_TRY
#define CEXCEPTION_HOOK_HAPPY_TRY
#endif
#ifndef CEXCEPTION_HOOK_AFTER_TRY
#define CEXCEPTION_HOOK_AFTER_TRY
#endif
#ifndef CEXCEPTION_HOOK_START_CATCH
#define CEXCEPTION_HOOK_START_CATCH
#endif
typedef struct {
  jmp_buf* pFrame;
  CEXCEPTION_T volatile Exception;
} CEXCEPTION_FRAME_T;
extern volatile CEXCEPTION_FRAME_T CExceptionFrames[];
#define Try                                                         \
    {                                                               \
        jmp_buf *PrevFrame, NewFrame;                               \
        unsigned int MY_ID = CEXCEPTION_GET_ID;                     \
        PrevFrame = CExceptionFrames[MY_ID].pFrame;                 \
        CExceptionFrames[MY_ID].pFrame = (jmp_buf*)(&NewFrame);     \
        CExceptionFrames[MY_ID].Exception = CEXCEPTION_NONE;        \
        CEXCEPTION_HOOK_START_TRY;                                  \
        if (setjmp(NewFrame) == 0) {                                \
            if (1)
#define Catch(e)                                                    \
            else { }                                                \
            CExceptionFrames[MY_ID].Exception = CEXCEPTION_NONE;    \
            CEXCEPTION_HOOK_HAPPY_TRY;                              \
        }                                                           \
        else                                                        \
        {                                                           \
            e = CExceptionFrames[MY_ID].Exception;                  \
            (void)e;                                                \
            CEXCEPTION_HOOK_START_CATCH;                            \
        }                                                           \
        CExceptionFrames[MY_ID].pFrame = PrevFrame;                 \
        CEXCEPTION_HOOK_AFTER_TRY;                                  \
    }                                                               \
    if (CExceptionFrames[CEXCEPTION_GET_ID].Exception != CEXCEPTION_NONE)
void Throw(CEXCEPTION_T ExceptionID);
#define ExitTry() Throw(CEXCEPTION_NONE)
#endif
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
volatile CEXCEPTION_FRAME_T CExceptionFrames[CEXCEPTION_NUM_ID] = {{ 0 }};
#pragma GCC diagnostic pop
void Throw(CEXCEPTION_T ExceptionID){
    unsigned int MY_ID = CEXCEPTION_GET_ID;
    CExceptionFrames[MY_ID].Exception = ExceptionID;
    if (CExceptionFrames[MY_ID].pFrame){
        longjmp(*CExceptionFrames[MY_ID].pFrame, 1);
    }
    CEXCEPTION_NO_CATCH_HANDLER(ExceptionID);
}


#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{newException = 0xfe};
enum{MXSZ = 15};

int m, n;
char board[MXSZ][MXSZ];
char orig [MXSZ][MXSZ];
int  DI[4] = {-1, 1, 0, 0};
int  DJ[4] = {0, 0, -1, 1};
char DV[4] = {'v', '^', '>', '<'};


static inline bool inside(int i, int j){
    return 1 <= i && i <= m && 1 <= j && j <= n;
}
static inline bool isDigit(char c){
    return c >= '0' && c <= '9';
}

void attempt(int depth){
    int savei = -1, savej = -1;
    int MAX = 99;
    int minOptions = MAX;
    int maxExtension = 0;
    for (int i = 1; i <= m; i++){
        for (int j = 1; j <= m; j++){
            if (board[i][j] == '.'){
                int options = 0;
                int extension = MAX;
                for (int dir = 0; dir < 4; dir++){
                    int need = 1;
                    for (int ii = i + DI[dir], jj = j + DJ[dir]; inside(ii, jj); ii += DI[dir], jj += DJ[dir]){
                        char cur = board[ii][jj];
                        if (isDigit(cur)){
                            int val = cur - '0';
                            if (val >= need){
                                ++options;
                                extension = fmin(extension, need);
                            }
                            break;
                        }
                        if(cur == '.')
                            ++need;
                        if(cur != '.' && cur != DV[dir])
                            break;
                    }
                }
                if(options < minOptions || (options == minOptions && extension > maxExtension)){
                    savei = i;
                    savej = j;
                    minOptions = options;
                    maxExtension = extension;
                }
            }
        }
    }
    if(minOptions == 0)
        return ;
    if(minOptions == MAX)
        Throw(newException);
    int i = savei, j = savej;
    char save[15][15]; clr(save);
    for(int dir = 0; dir < 4; dir++){
        int need = 1;
        for (int ii = i + DI[dir], jj = j + DJ[dir]; inside(ii, jj); ii += DI[dir], jj += DJ[dir]){
            char cur = board[ii][jj];
            if (isDigit(cur)){
                int val = cur - '0';
                if (val >= need){
                    for (int x = i, y = j; x != ii || y != jj; x += DI[dir], y += DJ[dir]){
                        save[x][y] = board[x][y];
                        board[x][y] = DV[dir];
                    }
                    save[ii][jj] = board[ii][jj];
                    board[ii][jj] -= need;
                    attempt(depth + 1);
                    for (int x = i, y = j; x != ii || y != jj; x += DI[dir], y += DJ[dir]){
                        board[x][y] = save[x][y];
                    }
                    board[ii][jj] = save[ii][jj];
                }
                break;
            }
            if (cur == '.')
                ++need;
            if (cur != '.' && cur != DV[dir])
                break;
        }
    }
}

int main(){
    CEXCEPTION_T ex;
    m = in_nextInt();
    n = in_nextInt();

    for(int i = 0; i < m+2; i++)
        memset(board[i], ' ', n+2);
    getchar();
    for(int i=1; i<=m; i++){
        for(int j = 1; j <= n; j++)
            board[i][j] = getchar();
        getchar();
    }
    for(int i = 0; i < m+2; i++)
        for(int j = 0; j < n+2; j++)
            orig[i][j] = board[i][j];
    Try{
        attempt(0);
    }
    Catch(ex){
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(isDigit(board[i][j]))
                    printf("%c", orig[i][j]);
                else
                    printf("%c", board[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
