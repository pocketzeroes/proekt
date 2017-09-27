#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char*names[] = {"Monday",
                "Tuesday",
                "Wednesday",
                "Thursday",
                "Friday",
                "Saturday",
                "Sunday"};
char buff[16];
int main(){
    int idx;
    scanf("%s", &buff);
    if     (buff[0]=='M')               idx=0;
    else if(buff[0]=='T'&&buff[1]=='u') idx=1;
    else if(buff[0]=='W'              ) idx=2;
    else if(buff[0]=='T'&&buff[1]=='h') idx=3;
    else if(buff[0]=='F'              ) idx=4;
    else if(buff[0]=='S'&&buff[1]=='a') idx=5;
    else if(buff[0]=='S'&&buff[1]=='u') idx=6;
    int ans = 0;
    for (int m = 0; m < 12; m++) {
        for (int i = 0; i < days[m]; i++, idx = (idx + 1) % 7) {
            if (i == 12 && idx == 4)
                ans++;
        }
    }
    printf("%d\n", ans);
	return 0;
}
