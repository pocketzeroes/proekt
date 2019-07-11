#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}

enum{ MAXS = 100};

int rings[MAXS+2][MAXS+2];

int main(){
    int n, m;
    char ch;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n+2; i++)
        rings[i][0] = rings[i][m+1] = 0;
    for(int j=0; j<m+2; j++)
        rings[0][j] = rings[n+1][j] = 0;
    getchar();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ch = getchar();
            if (ch == '.')
                rings[i+1][j+1] = 0;
            else
                rings[i+1][j+1] = -1;
        }
        getchar();
    }
    bool changes = true;
    int rnum = 0;
    while (changes){
        changes = false;
        rnum++;
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if (rings[i][j] == -1 && (rings[i-1][j] == rnum-1 || rings[i][j-1] == rnum-1 || rings[i+1][j] == rnum-1 || rings[i][j+1] == rnum-1)){
                    rings[i][j] = rnum;
                    changes = true;
                }
            }
        }
    }
    int width = 2;
    char*blanks = strdup("..");
    if (rnum>=10){
        width = 3;
        blanks = strdup("...");
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if (rings[i][j] == 0)
                printf("%s", blanks);
            else if(rings[i][j] >= 10)
                printf("%s%d", substr(blanks, 0, width-2), rings[i][j]);
            else
                printf("%s%d", substr(blanks, 0, width-1), rings[i][j]);
        }
        puts("");
    }
    return 0;
}
