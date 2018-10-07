bool ok(char c){
    return c >= 'A' && c <= 'Z' ||
           c >= 'a' && c <= 'z';
}
char*reverseOnlyLetters(char*s){
    int s_length = strlen(s);
    for(int i = 0, j = s_length-1; i < j;i++,j--){
        while(i < s_length && !ok(s[i]))
            i++;
        while(j >= 0 && !ok(s[j]))
            j--;
        if(i < j){
            char d = s[i];
            s[i] = s[j];
            s[j] = d;
        }
    }
    return strdup(s);
}
