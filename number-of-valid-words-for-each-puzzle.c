enum{ LETTERS = 26};
int*findNumOfValidWords(char**words, int wordsSz, char**puzzles, int puzzlesSz, int*rsz){
    int*freq=calloc(1<<LETTERS, sizeof(int));
    for(int z=0;z<wordsSz;z++){char*word = words[z];
        int mask = 0;
        for(int q=0;word[q];q++){char c = word[q];
            mask |= 1 << (c - 'a');
        }
        freq[mask]++;
    }
    int*answer = calloc(puzzlesSz, sizeof(int));
    for(int z=0;z<puzzlesSz;z++){char*puzzle = puzzles[z];
        int mask = 0;
        for(int q=0;puzzle[q];q++){char c = puzzle[q];
            mask |= 1 << (c - 'a');
        }
        int first = puzzle[0] - 'a';
        int sub = mask;
        int total = 0;
        while(1){
            if(sub >> first & 1)
                total += freq[sub];
            if(sub == 0)
                break;
            sub = (sub - 1) & mask;
        }
        answer[z] = total;
    }
    free(freq);
   *rsz=   puzzlesSz;
    return answer;
}
