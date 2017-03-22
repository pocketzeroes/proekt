int count(char*str,char chr){
    int sum=0;
    for(int i=0;str[i];i++){
        if(str[i]==chr)
            sum++;
    }
    return sum;
}
int longestPalindrome(char*s) {
    int odds = 0;
    for(char c = 'A'; c <= 'z'; ++c)
        odds += count(s, c) & 1;
    return strlen(s) - odds + (odds > 0);
}
        