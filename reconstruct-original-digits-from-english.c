char numbers[10][6]={"zero", "one", "two", "three","four", "five", "six", "seven","eight", "nine"};
int cmp(const void *a, const void *b) {   return *(char*)a - *(char*)b; }
char*originalDigits(char* s) {
    int cnts[10][26];memset(cnts,0,sizeof(cnts));
    for (int i = 0; i < 10; ++i) {
        char*str=numbers[i];
        for (int z=0;str[z];z++){
            int c=str[z];
            ++cnts[i][c - 'a'];
        }
    }
    int order[]={0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    char unique_chars[]={'z', 'o', 'w', 't', 'u', 'f', 'x', 's', 'g', 'n'};
    int cnt[26]={0};
    for (int z=0;s[z];z++){
        int c=s[z];
        ++cnt[c - 'a'];
    }
    char*result=malloc(90096);
    int  resultLen=0;
    for (int z=0;z<10;z++){
        int i=order[z];
        while (cnt[unique_chars[i] - 'a'] > 0) {
            for (int j = 0; j < 26; ++j) {
                cnt[j] -= cnts[i][j];
            }
            result[resultLen++]=(i + '0');
        }
    }
    result[resultLen]='\0';
    qsort(result, resultLen,1,cmp);
    return result;
}
