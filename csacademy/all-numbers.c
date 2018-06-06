#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
enum{ kMod =(int) 1e9 + 7};

int Pow(int a, int p){
    int r = 1;
    while (p) {
        if (p & 1)
            r = 1LL * r * a % kMod;
        a = 1LL * a * a % kMod;
        p /= 2;
    }
    return r;
}
int Inv(int a) {
    return Pow(a, kMod - 2);
}
int GetSum(int*num){
    int fact = 1;
    int num_digits = 0;
    for (int i = 0; i < 10; i += 1)
        num_digits += num[i];
    for (int i = 1; i <= num_digits; i += 1)
        fact = 1LL * fact * i % kMod;
    for (int i = 0; i < 10; i += 1) {
        int f = 1;
        for (int j = 1; j <= num[i]; j += 1)
            f = 1LL * f * j % kMod;
        fact = 1LL * fact * Inv(f) % kMod;
    }
    int numbers_sum = 0;
    for (int e = 1, i = 0; i < num_digits; e = 1LL * e * 10 % kMod, i += 1) {
        e %= kMod;
        numbers_sum += e;
        numbers_sum %= kMod;
    }
    int sum = 0;
    for (int i = 0; i < 10; i += 1) {
        if (num[i] == 0)
            continue;
        int f = fact;
        f = 1LL * f * num[i] % kMod;
        f = 1LL * f * Inv(num_digits) % kMod;
        sum += 1LL * f * numbers_sum % kMod * i % kMod;
        sum %= kMod;
    }
    return sum;
}
int main(){
    int num[10]; memset(num, 0, sizeof(num));
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int d;
        scanf("%d", &d);
        num[d]++;
    }
    int all_sum = GetSum(num);
    if(num[0]){
        num[0]--;
        all_sum -= GetSum(num);
        if (all_sum < 0)
            all_sum += kMod;
    }
    printf("%d\n", all_sum);
    return 0;
}
