#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

void testcase(){
    char*str = getstr();
    bool reached  = true, 
         reached1 = false,
         reached2 = false;
    for (size_t i = 0; str[i]; ++i){
        reached2 = reached1;
        reached1 = reached;
        reached = false;
        if (reached1) {
            if (str[i]=='b') reached = true;
            if (str[i]=='c') reached = true;
            if (str[i]=='f') reached = true;
            if (str[i]=='h') reached = true;
            if (str[i]=='i') reached = true;
            if (str[i]=='k') reached = true;
            if (str[i]=='n') reached = true;
            if (str[i]=='o') reached = true;
            if (str[i]=='p') reached = true;
            if (str[i]=='s') reached = true;
            if (str[i]=='u') reached = true;
            if (str[i]=='v') reached = true;
            if (str[i]=='w') reached = true;
            if (str[i]=='y') reached = true;
        }
        if (reached2) {
            if (str[i-1]=='a' && str[i]=='c') reached = true;
            if (str[i-1]=='a' && str[i]=='g') reached = true;
            if (str[i-1]=='a' && str[i]=='l') reached = true;
            if (str[i-1]=='a' && str[i]=='m') reached = true;
            if (str[i-1]=='a' && str[i]=='r') reached = true;
            if (str[i-1]=='a' && str[i]=='s') reached = true;
            if (str[i-1]=='a' && str[i]=='t') reached = true;
            if (str[i-1]=='a' && str[i]=='u') reached = true;
            if (str[i-1]=='b' && str[i]=='a') reached = true;
            if (str[i-1]=='b' && str[i]=='e') reached = true;
            if (str[i-1]=='b' && str[i]=='h') reached = true;
            if (str[i-1]=='b' && str[i]=='i') reached = true;
            if (str[i-1]=='b' && str[i]=='k') reached = true;
            if (str[i-1]=='b' && str[i]=='r') reached = true;
            if (str[i-1]=='c' && str[i]=='a') reached = true;
            if (str[i-1]=='c' && str[i]=='d') reached = true;
            if (str[i-1]=='c' && str[i]=='e') reached = true;
            if (str[i-1]=='c' && str[i]=='f') reached = true;
            if (str[i-1]=='c' && str[i]=='l') reached = true;
            if (str[i-1]=='c' && str[i]=='m') reached = true;
            if (str[i-1]=='c' && str[i]=='n') reached = true;
            if (str[i-1]=='c' && str[i]=='o') reached = true;
            if (str[i-1]=='c' && str[i]=='r') reached = true;
            if (str[i-1]=='c' && str[i]=='s') reached = true;
            if (str[i-1]=='c' && str[i]=='u') reached = true;
            if (str[i-1]=='d' && str[i]=='b') reached = true;
            if (str[i-1]=='d' && str[i]=='s') reached = true;
            if (str[i-1]=='d' && str[i]=='y') reached = true;
            if (str[i-1]=='e' && str[i]=='r') reached = true;
            if (str[i-1]=='e' && str[i]=='s') reached = true;
            if (str[i-1]=='e' && str[i]=='u') reached = true;
            if (str[i-1]=='f' && str[i]=='e') reached = true;
            if (str[i-1]=='f' && str[i]=='l') reached = true;
            if (str[i-1]=='f' && str[i]=='m') reached = true;
            if (str[i-1]=='f' && str[i]=='r') reached = true;
            if (str[i-1]=='g' && str[i]=='a') reached = true;
            if (str[i-1]=='g' && str[i]=='d') reached = true;
            if (str[i-1]=='g' && str[i]=='e') reached = true;
            if (str[i-1]=='h' && str[i]=='e') reached = true;
            if (str[i-1]=='h' && str[i]=='f') reached = true;
            if (str[i-1]=='h' && str[i]=='g') reached = true;
            if (str[i-1]=='h' && str[i]=='o') reached = true;
            if (str[i-1]=='h' && str[i]=='s') reached = true;
            if (str[i-1]=='i' && str[i]=='n') reached = true;
            if (str[i-1]=='i' && str[i]=='r') reached = true;
            if (str[i-1]=='k' && str[i]=='r') reached = true;
            if (str[i-1]=='l' && str[i]=='a') reached = true;
            if (str[i-1]=='l' && str[i]=='i') reached = true;
            if (str[i-1]=='l' && str[i]=='r') reached = true;
            if (str[i-1]=='l' && str[i]=='u') reached = true;
            if (str[i-1]=='l' && str[i]=='v') reached = true;
            if (str[i-1]=='m' && str[i]=='d') reached = true;
            if (str[i-1]=='m' && str[i]=='g') reached = true;
            if (str[i-1]=='m' && str[i]=='n') reached = true;
            if (str[i-1]=='m' && str[i]=='o') reached = true;
            if (str[i-1]=='m' && str[i]=='t') reached = true;
            if (str[i-1]=='n' && str[i]=='a') reached = true;
            if (str[i-1]=='n' && str[i]=='b') reached = true;
            if (str[i-1]=='n' && str[i]=='d') reached = true;
            if (str[i-1]=='n' && str[i]=='e') reached = true;
            if (str[i-1]=='n' && str[i]=='i') reached = true;
            if (str[i-1]=='n' && str[i]=='o') reached = true;
            if (str[i-1]=='n' && str[i]=='p') reached = true;
            if (str[i-1]=='o' && str[i]=='s') reached = true;
            if (str[i-1]=='p' && str[i]=='a') reached = true;
            if (str[i-1]=='p' && str[i]=='b') reached = true;
            if (str[i-1]=='p' && str[i]=='d') reached = true;
            if (str[i-1]=='p' && str[i]=='m') reached = true;
            if (str[i-1]=='p' && str[i]=='o') reached = true;
            if (str[i-1]=='p' && str[i]=='r') reached = true;
            if (str[i-1]=='p' && str[i]=='t') reached = true;
            if (str[i-1]=='p' && str[i]=='u') reached = true;
            if (str[i-1]=='r' && str[i]=='a') reached = true;
            if (str[i-1]=='r' && str[i]=='b') reached = true;
            if (str[i-1]=='r' && str[i]=='e') reached = true;
            if (str[i-1]=='r' && str[i]=='f') reached = true;
            if (str[i-1]=='r' && str[i]=='g') reached = true;
            if (str[i-1]=='r' && str[i]=='h') reached = true;
            if (str[i-1]=='r' && str[i]=='n') reached = true;
            if (str[i-1]=='r' && str[i]=='u') reached = true;
            if (str[i-1]=='s' && str[i]=='b') reached = true;
            if (str[i-1]=='s' && str[i]=='c') reached = true;
            if (str[i-1]=='s' && str[i]=='e') reached = true;
            if (str[i-1]=='s' && str[i]=='g') reached = true;
            if (str[i-1]=='s' && str[i]=='i') reached = true;
            if (str[i-1]=='s' && str[i]=='m') reached = true;
            if (str[i-1]=='s' && str[i]=='n') reached = true;
            if (str[i-1]=='s' && str[i]=='r') reached = true;
            if (str[i-1]=='t' && str[i]=='a') reached = true;
            if (str[i-1]=='t' && str[i]=='b') reached = true;
            if (str[i-1]=='t' && str[i]=='c') reached = true;
            if (str[i-1]=='t' && str[i]=='e') reached = true;
            if (str[i-1]=='t' && str[i]=='h') reached = true;
            if (str[i-1]=='t' && str[i]=='i') reached = true;
            if (str[i-1]=='t' && str[i]=='l') reached = true;
            if (str[i-1]=='t' && str[i]=='m') reached = true;
            if (str[i-1]=='x' && str[i]=='e') reached = true;
            if (str[i-1]=='y' && str[i]=='b') reached = true;
            if (str[i-1]=='z' && str[i]=='n') reached = true;
            if (str[i-1]=='z' && str[i]=='r') reached = true;
        }
    }
    puts(reached ? "YES" : "NO");
}

int main(){
    int t;
    scanf("%d", &t);
    for(int i=0; i<t; i++)
        testcase();
    return 0;
}
