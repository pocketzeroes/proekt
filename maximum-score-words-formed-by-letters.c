#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
enum{ ALPHABET = 26};

int min_element(int*arr, int sz){
  int mine = arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]<mine)
      mine=arr[i];
  return mine;
}

int maxScoreWords(char**words, int wordsSz, char*letters, int lettersSz, int*score, int scoreSz){
    int W = wordsSz;
    int letter_count[ALPHABET]; clr(letter_count);
    for(int z=0;z<lettersSz;z++){char c = letters[z];
        letter_count[c - 'a']++;
    }
    int best = 0;
    for(int mask = 0; mask < 1 << W; mask++){
        int save[ALPHABET]; memcpy(save, letter_count, sizeof(save));
        int sum = 0;
        for(int i = 0; i < W; i++){
            if(mask >> i & 1){
                for(int c = 0; c < ALPHABET; c++){
                    int count(char*str, char chr){
                        int cnt=0;
                        for(int z=0;str[z];z++){char c=str[z];
                            if(c==chr)
                                cnt++;
                        }
                        return cnt;
                    }
                    int occur = count(words[i], 'a'+c);
                    letter_count[c] -= occur;
                    sum += score[c] * occur;
                }
            }
        }
        if(min_element(letter_count, ALPHABET) >= 0)
            best = fmax(best, sum);
        memcpy(letter_count, save, sizeof(save));
    }
    return best;
}
