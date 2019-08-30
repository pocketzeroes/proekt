#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int number_of_stones;
    scanf("%d", &number_of_stones);
    if(number_of_stones%2==0)
        puts("Bob");
    else
        puts("Alice");
    return 0;
}
