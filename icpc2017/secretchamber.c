#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum{ MAXK = 10 + 36 + 3};
enum{ MAXL = 50 + 3     };

int get_id(char ch)
{
    return (('0' <= ch && ch <= '9')? ch - '0' : ch- 'a' + 10);
}
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);
    bool mat[MAXK][MAXK];
    memset(mat, 0 , sizeof(mat));
    for(int i = 0; i < MAXK; ++i) 
        mat[i][i] = true;
    char ch1[2], ch2[2];
    while(m--){
        scanf("%s %s", ch1, ch2);
        mat[get_id(ch1[0])][get_id(ch2[0])] = true;
    }
    for(int k = 0; k < MAXK; ++k)
        for(int i = 0; i < MAXK; ++i)
            for(int j = 0; j < MAXK; ++j)
                if(mat[i][k] && mat[k][j])
                    mat[i][j] = true;
    char word1[MAXL], word2[MAXL];
    while(n--) {
        scanf("%s %s", word1, word2);
        int len1 = strlen(word1), len2 = strlen(word2);
        bool ans = true;
        if(len1 == len2) {
            for(int i = 0; i < len1; ++i) {
                if(mat[get_id(word1[i])][get_id(word2[i])] == false) {
                    ans = false;
                    break;
                }
            }
        }
        else ans = false;
        puts((ans)? "yes" : "no");
    }
    return 0;
}
