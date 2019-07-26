#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int swap(char *s, char *t, size_t size){
    size_t a = 0, b = 0, moves = 0;
    while(1){
        while (a < size && !(s[a] != t[a] && s[a] == '0'))
            ++a;
        while (b < size && !(s[b] != t[b] && s[b] == '1'))
            ++b;
        if (a < size && b < size) {
            s[a] = t[a];
            s[b] = t[b];
            ++moves;
        }
        else
            break;
    }
    return moves;
}
int min_moves(char *s, char *t){
    int moves = 0, zeroes = 0;
    size_t size = strlen(s);
    moves += swap(s, t, size);
    for (size_t i = 0; i < size; ++i)
        if (s[i] == '0' && t[i] == '1') {
            s[i] = '1';
            moves++;
        }
    for (size_t i = 0; i < size; ++i)
        if (s[i] == '1' && t[i] == '0')
            zeroes++;
    for (size_t i = 0; i < size; ++i)
        if (s[i] == '?') {
            if (t[i] == '1' && zeroes > 0) {
                s[i] = '0';
                zeroes--;
            }
            else
                s[i] = t[i];
            moves++;
        }
    moves += swap(s, t, size);
    if (strcmp(s, t) != 0)
        return -1;
    return moves;
}
int main(){
    int n;
    char s[201], t[201];
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%s%s", s, t);
        printf("Case %d: %d\n", i, min_moves(s, t));
    }
    return EXIT_SUCCESS;
}
