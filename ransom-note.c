#include<stdio.h>
#include<stdbool.h>

bool canConstruct(char* ransomNote, char* magazine) {
    int counts[26]={0};
    int letters = 0;
    for(int i=0; ransomNote[i]; i++){
        char c=ransomNote[i];
        if (counts[c - 'a']++ == 0)
            ++letters;
    }
    for (int i=0; magazine[i]; i++) {
        char c=magazine[i];
        if (--counts[c - 'a'] == 0 && --letters == 0)
            break;
    }
    return letters == 0;
}

int main(){
    puts((canConstruct("a", "b")   ==true)?"true":"false");  // expected false
    puts((canConstruct("aa", "ab") ==true)?"true":"false");  // expected false
    puts((canConstruct("aa", "aab")==true)?"true":"false");  // expected true
    return 0;
}

