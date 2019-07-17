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


int tonum(char*note){
    if(strcmp(note, "A") ==0) return 0;
    if(strcmp(note, "A#")==0) return 1;
    if(strcmp(note, "B") ==0) return 2;
    if(strcmp(note, "C") ==0) return 3;
    if(strcmp(note, "C#")==0) return 4;
    if(strcmp(note, "D") ==0) return 5;
    if(strcmp(note, "D#")==0) return 6;
    if(strcmp(note, "E") ==0) return 7;
    if(strcmp(note, "F") ==0) return 8;
    if(strcmp(note, "F#")==0) return 9;
    if(strcmp(note, "G") ==0) return 10;
    if(strcmp(note, "G#")==0) return 11;
}
char*tonote(int n){
    switch(n){
        case 0: return "A";
        case 1: return "A#";
        case 2: return "B";
        case 3: return "C";
        case 4: return "C#";
        case 5: return "D";
        case 6: return "D#";
        case 7: return "E";
        case 8: return "F";
        case 9: return "F#";
        case 10:return "G";
        case 11:return "G#";
    }
}
bool inscale(bool*ournotes, int*scale){
    bool works = true;
    for(int i = 0; i < 12; i++){
        bool inthisscale = false;
        for(int j = 0; j < 7; j++){
            if(scale[j] == i)
                inthisscale = true;
        }
        if(ournotes[i] && !inthisscale)
            works = false;
    }
    return works;
}
int main(){
    int notes;
    scanf("%d", &notes);
    int scales[12][7] = {
        {0,2,4,5,7,9,11},
        {1,3,5,6,8,10,0},
        {2,4,6,7,9,11,1},//3
        {3,5,7,8,10,0,2},
        {4,6,8,9,11,1,3},
        {5,7,9,10,0,2,4},//6
        {6,8,10,11,1,3,5},
        {7,9,11,0,2,4,6},
        {8,10,0,1,3,5,7},//9
        {9,11,1,2,4,6,8},
        {10,0,2,3,5,7,9},
        {11,1,3,4,6,8,10}//12
    };
    bool ournotes[12]={false};
    for(int i=0; i<notes; i++){
        char*note = getstr();
        ournotes[tonum(note)] = true;
    }
    bool printed = false;
    for(int i=0; i<12; i++){
        if(inscale(ournotes, scales[i])){
            printed = true;
            printf("%s ", tonote(i));
        }
    }
    if(!printed)
        puts("none");
    puts("");
    return 0;
}
