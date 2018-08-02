#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, x;
    scanf("%d %d", &n, &x);
    int sum_d = 0;
    int carry = 0; 
    int num_zero = 0;  
    while(n % 10 == 0){
        num_zero++; 
        n /= 10; 
    }
    while(sum_d <= x){
        int p = n % 10; 
        int d = 10 - (carry + p); 
        sum_d += d; 
        carry = 1; 
        num_zero++; 
        n /= 10; 
    }
    printf("%d\n", num_zero - 1); 
    return 0;
}
