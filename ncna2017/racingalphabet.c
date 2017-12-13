#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}

char line[100000];
int main(){
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ '";
    double length = (60. * M_PI) / 28.;
    double passed;
    double currPos;
    double nextPos;
    int n;
    scanf("%d", &n);
    fgets(line, 1000, stdin);
    for (int i = 0; i < n; i++){
        fgets(line, 1000, stdin);
        currPos = strchr(alphabet, line[0]) - alphabet;
        passed = 0;
        int line_len=strlen(line);
        line_len--;
        for (int j = 1, m = line_len; j < m; j++){
            nextPos = strchr(alphabet, line[j]) - alphabet;
            passed += min(abs(currPos - nextPos), 28 - abs(currPos - nextPos));
            currPos = nextPos;
        }
        printf("%lf\n", (double) (((passed * length) / 15.) + line_len));
    }
}
