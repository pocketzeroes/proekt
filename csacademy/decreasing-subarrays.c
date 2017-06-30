#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int main() {
    int n; 
    scanf("%d", &n);
    int last_element = 1e9;
    int length = 0;
    for (int i = 0; i < n; i += 1) {
        int x;
        scanf("%d", &x);
        if (x < last_element){
            length++;
        }
        else{
            for (int j = 0; j < length; j++){
                printf("%d ", length);
            }
            length = 1;
        }
        last_element = x;
    }
    for (int j = 0; j < length; j++){
        printf("%d ", length);
    }
    return 0;
}
