#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int minOperations(char*s){
    int freq[4]; clr(freq);
    for(int i=0; s[i]; i++){
        int k = (s[i] - '0') * 2 + (i % 2);
        ++freq[k];
    }
    return fmin(freq[0] + freq[3], freq[1] + freq[2]);
}
