#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

static int END = INT_MAX / 2;

typedef struct{
    int*start,*end;
}Phrase;

int *fromPhraseOptimals;
Phrase *phraseArray;
int optimalFromPhrase(Phrase *phrases);

int find(int*arr, int sz, int val){
    int i;
    for(i=0; i<sz; i++)
        if(arr[i]==val)
            return i;
    return i;
}
int optimizeFromPhrase(Phrase *phrases){
    int maxBonus = -1;
    int sp = 0;
    int *noteAt = phrases->start;
    int *noteAfter = noteAt;
    Phrase *activePhrase = phrases;
    Phrase *phraseAfter = activePhrase + 1;
    while(1){
        noteAt++;
        if (*activePhrase->start < END){
            if (noteAt > activePhrase->start)
                sp += *noteAt - *(noteAt - 1);
            if (noteAt == activePhrase->end)
                activePhrase++;
        }
        while (*noteAfter < *noteAt + sp){
            noteAfter++;
            if (*noteAfter == END)
                return max(maxBonus, noteAfter - noteAt);
        }
        while (noteAfter > phraseAfter->start){
            maxBonus = max(maxBonus, phraseAfter->start - noteAt + optimalFromPhrase(phraseAfter));
            phraseAfter++;
        }
        maxBonus = max(maxBonus, noteAfter - noteAt + optimalFromPhrase(phraseAfter));
    }
}
int optimalFromPhrase(Phrase *phrases){
    int offset = phrases - phraseArray;
    if (fromPhraseOptimals[offset] == -1)
        fromPhraseOptimals[offset] = optimizeFromPhrase(phrases);
    return fromPhraseOptimals[offset];
}
int main(){
    int n, p;
    scanf("%d%d", &n, &p);
    int*notes = calloc(n+1, sizeof(int));
    for(int i=0; i<n; ++i)
        scanf("%d", &notes[i]);
    notes[n] = END;
    Phrase*phrases = calloc(p+1, sizeof(Phrase));
    for(int i=0; i<p; ++i){
        int start, end;
        scanf("%d %d", &start, &end);
        phrases[i].start = &notes[find(notes, n, start)];
        phrases[i].end   = &notes[find(notes, n, end  )];
    }
    phrases[p] =(Phrase){ &notes[n], &notes[n] };
    fromPhraseOptimals = calloc(p+1, sizeof(int));
    for(int i=0; i<p; ++i)
        fromPhraseOptimals[i] = -1;
    fromPhraseOptimals[p] = 0;
    phraseArray = phrases;
    printf("%d\n", n + optimalFromPhrase(&phrases[0]));
    return 0;
}
