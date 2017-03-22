char* intToRoman(int num) {
    int   nums     [] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char  romans[][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    char* result=malloc(4096);
    memset(result, 0, 4096);
    int resLen=0;
    int   i = 0;
    while (num > 0) {
        int times = num / nums[i];
        while (times--) {
            num -= nums[i];
            strcat(result, romans[i]);
            resLen+=strlen(romans[i]);
        }
        ++i;
    }        
    result[resLen]='\0';
    return result;
}
