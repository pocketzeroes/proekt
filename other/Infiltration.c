#include <stdio.h>
#include <string.h>

enum{ MAXC = 201};
enum{ MAXW = 100};
char words[MAXW][MAXC];
int  wcnt;
int  wmap   [MAXW];
char amap   [256],
     bmap   [256];
int  amapcnt[256], 
     bmapcnt[256];
int  found_sol = 0;
int  ambig = 0;

enum{ kwcnt = 12};
char kwords[kwcnt][MAXC]={{"be"},{"will"},{"our"},{"rum"},{"dead"},{"hook"},{"ship"},{"blood"},{"sable"},{"avenge"},{"parrot"},{"captain"}};
char sol[256];
int seen[256];

void rec_map(int kwix){
    int i;
    int wix;
    char c;
    int no_mapping = 0;
    for (c='a';c<='z' && !no_mapping;c++){
        no_mapping = (seen[c] && !amapcnt[c]);
    }
    if (!no_mapping){
        if (found_sol){
            int same = 1;
            for (c='a';c<='z' && same;c++) {
                same = amap[c]==sol[c];
            }
            if (!same)
                ambig = 1;
        }
        else{
            found_sol = 1;
            for(c='a';c<='z';c++)
                sol[c] = amap[c];
        }
    }
    else if (kwix<kwcnt){
        for (wix = 0; wix < wcnt && !ambig; wix++){
            if (wmap[wix]==0 && strlen(words[wix])==strlen(kwords[kwix])){
                int match = 1,last = -1;
                for (i=0;i<strlen(kwords[kwix]) && match;i++){
                    match = !((amapcnt[words[wix][i]] && (amap[words[wix][i]]!=kwords[kwix][i])) || (bmapcnt[kwords[kwix][i]] && (bmap[kwords[kwix][i]]!=words[wix][i])));
                    if (match){
                        amapcnt[words[wix][i]]++;
                        amap[words[wix][i]]=kwords[kwix][i];
                        bmapcnt[kwords[kwix][i]]++;
                        bmap[kwords[kwix][i]]=words[wix][i];
                        last = i;
                    }
                }
                if (match) {
                    wmap[wix] = 1;
                    rec_map(kwix+1);
                    wmap[wix] = 0;
                }
                for (i=0;i<last+1;i++) {
                    amapcnt[words[wix][i]]--;
                    bmapcnt[kwords[kwix][i]]--;
                }
            }
        }
        rec_map(kwix+1);
    }
}
int main(){
    char c;
    int i,j;
    wcnt = 0;
    for(c='a'; c<='z'; c++)
        seen[c] = 0;
    while(scanf("%s",words[wcnt])!=EOF){
        for(i=0;i<strlen(words[wcnt]);i++)
            seen[words[wcnt][i]]=1;
        wcnt++;
    }
    for(c='a'; c<='z'; c++)
        amapcnt[c] = bmapcnt[c] = 0;
    for(i=0; i<wcnt; i++)
        wmap[i] = 0;
    rec_map(0);
    if(!ambig && found_sol){
        for(i=0; i<wcnt; i++){
            for(j=0;j<strlen(words[i]);j++)
                printf("%c",sol[words[i][j]]);
            if (i<wcnt-1)
                printf(" ");
        }
        printf("\n");
    }
    else
        printf("Impossible\n");
    return 0;
}
