char* convertToBase7(int num) {
    if (num == 0) return "0";
    int sign = (num > 0 ? 1 : -1);
    long res = 0; 
    int digit = 1;
    num *= sign;
    while (num > 0) {
        res += (num % 7) * digit;
        digit *= 10;
        num /= 7;
    }
    char buff[32];
    sprintf(buff,"%d",res * sign);
    return strdup(buff);
}
