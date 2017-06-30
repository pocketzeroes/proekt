#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

char s[1000];

int main() {
    int n; 
    scanf("%d", &n);
    int num_letters[26];
    memset(num_letters, 0, sizeof(num_letters));
    for (int i = 0; i < n; i += 1) {
        getchar();
        char c=getchar();
        num_letters[c - 'a'] += 1;
    }
    scanf("%s", &s);
    int answer = 0;
    for (int i = 0; s[i]; i++) {
        num_letters[s[i] - 'a'] -= 1;
    }
    for (int i = 0; i < 26; i += 1) {
        if (num_letters[i] < 0) {
            answer -= num_letters[i];
        }
    }
    printf("%d\n", answer);
    return 0;
}
