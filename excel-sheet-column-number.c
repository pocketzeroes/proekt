int titleToNumber(char* s) {
    int number = 0;
    for (int i=0; s[i]; i++) {
        char c = s[i];
        number *= 26;
        number += c  - 'A' + 1;
    }
    return number;
}
