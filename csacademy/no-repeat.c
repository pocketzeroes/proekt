#include <stdio.h>
char buff[100000];
int main(){
    int n;
    scanf("%d", &n);
    scanf("%s", &buff);
    int len = strlen(buff);
    for(int i=0; i<len; i++){char ch = buff[i];
        int cnt_equal = 0;
        for(int j=0; j<len; j++){char oth = buff[j];
            if(ch == oth)
                cnt_equal++;
        }
        if(cnt_equal == 1){
            printf("%c\n", ch);
            return 0;
        }
    }
    puts("-1");
}
