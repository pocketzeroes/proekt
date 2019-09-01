#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushbackF(zpv.ptr, &zpv.sz, zvv)
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct Fact {
    int p1_type, p1;
    int p2_type, p2;
    int relation;
}Fact;
typedef Fact* Factp;
Fact*newFact(){
    return calloc(1, sizeof(Fact));
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Factp*pushbackF(Factp*array, int *size, Factp value){
  Factp*output = resizeArray(array, Factp, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Factp*ptr;
	int sz;
}vecf;
vecf newVecF(){
	vecf rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int amigaPerson;
int roomTypeProp[5][6]; 
int typePropRoom[6][5]; 
vecf propFacts[6][5];//of Factp

char*props[] = {
    "1", "2", "3", "4", "5",
    "blue", "green", "red", "white", "yellow",
    "anna", "bernhard", "chris", "david", "ellen",
    "danish", "finnish", "icelandic", "norwegian", "swedish",
    "amiga", "atari", "linux", "mac", "windows",
    "c", "c++", "java", "pascal", "perl" };

bool check(Factp*v, int vsz){
    for (int i = 0; i < vsz; i++) {
        int r1 = typePropRoom[v[i]->p1_type][v[i]->p1];
        int r2 = typePropRoom[v[i]->p2_type][v[i]->p2];
        if (r1 >= 0 && r2 >= 0){
            switch (v[i]->relation) {
              case 0: if (r1 != r2) return false; break;
              case 1: if (r2 - r1 != 1) return false; break;
              case 2: if (r1 - r2 != 1) return false; break;
              case 3: if (r1 - r2 != 1 && r2 - r1 != 1) return false; break;
            }
        }
    }
    return true;
}
bool solver(){
    if (amigaPerson >= 0 && typePropRoom[4][0] >= 0 && roomTypeProp[typePropRoom[4][0]][2] == amigaPerson){
        return false;
    }
    int best = -1, type, prop;
    for (int i = 1; i < 6; i++){
        for (int j = 0; j < 5; j++){
            if (typePropRoom[i][j] < 0) {
                int poss = 0;
                for (int k = 0; k < 5; k++){
                    if (roomTypeProp[k][i] < 0) {
                        typePropRoom[i][j] = k;
                        if (check(propFacts[i][j].ptr, propFacts[i][j].sz)) 
                            poss++;
                        typePropRoom[i][j] = -1;
                    }
                }
                if (!poss) 
                    return false;
                if (best < 0 || poss < best) {
                    best = poss;
                    type = i;
                    prop = j;
                }
            }
        }
    }
    if (best < 0) {
        int person = roomTypeProp[typePropRoom[4][0]][2];
        if (amigaPerson >= 0 && amigaPerson != person) {
            amigaPerson = -1; 
            return true;
        }
        amigaPerson = person;
        return false; 
    }
    for (int k = 0; k < 5; k++){
        if (roomTypeProp[k][type] < 0) {
            typePropRoom[type][prop] = k;
            if(check(propFacts[type][prop].ptr, propFacts[type][prop].sz)){
                roomTypeProp[k][type] = prop;
                if (solver()) 
                    return true;
                roomTypeProp[k][type] = -1;
            }
            typePropRoom[type][prop] = -1;
        }
    }
    return false;
}
int main(){
    int nuoTestCases, nuoFacts;
    char*p1;
    char*r;
    char*p2;
    scanf("%d", &nuoTestCases);
    for (int scenarioNo = 1; scenarioNo <= nuoTestCases; scenarioNo++) {
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 5; j++) {
                propFacts[i][j].sz=0;
                roomTypeProp[j][i] = i ? -1 : j;
                typePropRoom[i][j] = i ? -1 : j;
            }
        }
        scanf("%d", &nuoFacts);
        Factp facts[nuoFacts];
        for(int i = 0; i < nuoFacts; i++) {
            p1=getstr();
            r =getstr();
            p2=getstr();
            Factp f = newFact();
            facts[i] = f;
            f->p1 = f->p2 = f->relation = -1;
            for(int j = 0; j < 30; j++){
                if(strcmp(p1, props[j])==0){
                    f->p1_type = j / 5;
                    f->p1 = j % 5;
                    pb(propFacts[f->p1_type][f->p1], f);
                }
                if(strcmp(p2, props[j])==0){
                    f->p2_type = j / 5;
                    f->p2 = j % 5;
                    pb(propFacts[f->p2_type][f->p2], f);
                }
            }
            if     (strcmp(r, "same-as" )==0)f->relation = 0;
            else if(strcmp(r, "left-of" )==0)f->relation = 1;
            else if(strcmp(r, "right-of")==0)f->relation = 2;
            else if(strcmp(r, "next-to" )==0)f->relation = 3;
        }
        printf("scenario #%d: ", scenarioNo);
        amigaPerson = -2;
        if(check(facts, nuoFacts))
            solver();
        if (amigaPerson == -1)
            puts("cannot identify the amiga owner.");
        else if (amigaPerson == -2)
            puts("impossible.");
        else
            printf("%s owns the amiga.\n", props[amigaPerson + 10]);
        for (int i = 0; i < nuoFacts; i++){
            free(facts[i]);
        }
    }
    return 0;
}
