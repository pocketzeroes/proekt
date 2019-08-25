int calculateTime(char*keyboard, char*word){
    int pos = 0;
    int ans = 0;
    for(int i=0;word[i];i++){char c = word[i];
        int p = strchr(keyboard, c)-keyboard;
        ans += abs(p - pos);
        pos = p;
    }
    return ans;
}
