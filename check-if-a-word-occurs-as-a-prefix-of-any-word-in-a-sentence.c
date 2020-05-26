int isPrefixOfWord(char*sentence, char*searchWord){
    int swlen = strlen(searchWord);
    int result = -1;
    for(int i=0, j=0, idx=1; sentence[i]; i++){
        if(sentence[i] == ' '){
            j = 0;
            idx++;
        }
        else if (j < 0){
            continue;
        }
        else if(sentence[i] == searchWord[j]){
            j++;
            if(j == swlen){
                result = idx;
                break;
            }
        }
        else {
            j = -1;
        }
    }
    return result;
}
