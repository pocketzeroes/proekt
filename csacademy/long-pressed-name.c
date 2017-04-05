#include <stdio.h>
#include<stdbool.h>

int main() {
    size_t len;
    char*a=NULL;
    char*b=NULL; 
    getline(&a, &len, stdin);
    getline(&b, &len, stdin);
    int itr_a = 0;
    int itr_b = 0;
    bool ok = true;
    while (itr_a < strlen(a) ) {
        char current_character = a[itr_a];
        int num_ch_a = 0, num_ch_b = 0;
        while (itr_a < strlen(a) && a[itr_a] == current_character) {
            itr_a += 1;
            num_ch_a += 1;
        }
        while (itr_b < strlen(b) && b[itr_b] == current_character) {
            itr_b += 1;
            num_ch_b += 1;
        }
        if (num_ch_a > num_ch_b) {
            ok = false;
        }
    }
    if (itr_b != strlen(b) ) {
        ok = false;
    }
    puts(ok?"1":"0");
    return 0;
}
