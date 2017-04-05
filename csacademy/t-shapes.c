#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef char* string;
string str[500];

int main(){
    int n, m;
    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; ++i){
        char buff[500];
        scanf("%499s",&buff);
        str[i]=strdup(buff);
    }
    int counter = 0;
    for (int i = 0; i + 2 < n; ++i) {
        for (int j = 1; j + 1 < m; ++j) {
            if (    str[i][j] == 't' && 
                    str[i][j - 1] == 't' && 
                    str[i][j + 1] == 't' && 
                    str[i + 1][j] == 't' && 
                    str[i + 2][j] == 't') {
                counter++;
            }
        }
    }
    printf("%d", counter );
    return 0;
}
