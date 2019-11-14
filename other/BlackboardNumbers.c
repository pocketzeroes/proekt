#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int isPrime(long n){
    double sqroot = sqrt(n);
    if (n > 2 && n % 2 == 0)
        return 0;
    for (long i = 3; i <= sqroot; i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}
int main(){
    int cases;
    scanf("%d", &cases);
    for(int i = 0; i < cases; i++){
        int primes = 0;
        char line[11];
        scanf("%s", line);
        long hexa = strtol(line, NULL, 16);
        if(hexa == 0 || hexa == 1){
            printf("0/1\n");
            continue;
        }
        if (isPrime(hexa))
            primes++;
        if (strstr(line, "A") != NULL ||
            strstr(line, "B") != NULL ||
            strstr(line, "C") != NULL ||
            strstr(line, "D") != NULL ||
            strstr(line, "E") != NULL ||
            strstr(line, "F") != NULL) {
              printf("%d/1\n", primes);
              continue;
        }
        if (isPrime(strtol(line, NULL, 10)))
            primes++;
        if (strstr(line, "8") != NULL || strstr(line, "9") != NULL) {
            if (primes == 2)
                printf("1/1\n");
            else if (primes == 1)
                printf("1/2\n");
            else
                printf("0/1\n");
            continue;
        }
        if (isPrime(strtol(line, NULL, 8)))
            primes++;
        if(strstr(line, "2") != NULL ||
           strstr(line, "3") != NULL ||
           strstr(line, "4") != NULL ||
           strstr(line, "5") != NULL ||
           strstr(line, "6") != NULL ||
           strstr(line, "7") != NULL){
            if (primes == 3)
                printf("1/1\n");
            else if (primes == 2)
                printf("2/3\n");
            else if (primes == 1)
                printf("1/3\n");
            else
                printf("0/1\n");
            continue;
        }
        if (isPrime(strtol(line, NULL, 2)))
            primes++;
        if (primes == 4)
            printf("1/1\n");
        else if (primes == 3)
            printf("3/4\n");
        else if (primes == 2)
            printf("1/2\n");
        else if (primes == 1)
            printf("1/4\n");
        else
            printf("0/1\n");
    }
    return 0;
}
