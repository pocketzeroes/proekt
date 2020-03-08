int lst[100];
int findTheLongestSubstring(char*s){
    memset(lst, -1, sizeof(lst));
    int h = 0;
    lst[h] = 0;
    int ans = 0, cur = 0;
    for(int z=0;s[z];z++){char c=s[z];
        ++cur;
        if (c == 'a') h ^= (1 << 0);
        else if (c == 'e') h ^= (1 << 1);
        else if (c == 'i') h ^= (1 << 2);
        else if (c == 'o') h ^= (1 << 3);
        else if (c == 'u') h ^= (1 << 4);
        if (lst[h] >= 0) ans = fmax(ans, cur - lst[h]);
        else lst[h] = cur;
    }
    return ans;
}
