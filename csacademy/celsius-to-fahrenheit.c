#include<stdio.h>
 
int main(){
    int celsius;
    float fahrenheit;
    scanf("%d", &celsius);
    fahrenheit = (1.8 * celsius) + 32;
    printf("%d", (int)fahrenheit);
    return 0;
}

