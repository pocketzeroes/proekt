#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 197};

void print2(char*s, int n){
    for(int i=n;i--;)
        printf("%s", s);
}
void print(char*s){
     print2(s, 1);
}
int main(){
    char*pat = strdup(">>>vvv<<^^^^^^^>>><<vvv");
    printf("%d\n", N);
    for(int i=(N- strlen(pat))/2;i-->0;)
        printf("><");
    printf("%s\n", pat);
    print2("#", N);
    puts("");
    print("#R");
    print2(".", N-3);
    puts("#");
    for (int i=(N-7)/5;i--;){
        print("#.");   print2("#", N-4); puts(".#");
        print("#.#");  print2("...#", (N-5)/4); puts(".#");
        print("#.#."); print2("#...", (N-5)/4); puts("#");
        print("#.#."); print2("#", N-4); puts("");
        print("#.#");  print2(".", N-4); puts("#");
    }
    print("#.");   print2("#", N-4); puts(".#");
    print("#.#");  print2("...#", (N-5)/4); puts(".#");
    print("#.#."); print2("#...", (N-5)/4); puts("#");
    print("#..."); print2("#", N-4); puts("");
    print2("#", N);
    puts("");
    return 0;
}
