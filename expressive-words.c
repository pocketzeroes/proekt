bool isok(char*a, char*b){
    int i = 0, j = 0;
    int a_length=strlen(a);
    int b_length=strlen(b);
    while(i < a_length && j < b_length){
        int ii = i + 1, jj = j + 1;
        while (ii < a_length && a[ii] == a[i]) ii++;
        while (jj < b_length && b[jj] == b[j]) jj++;
        int cnt1 = ii - i, cnt2 = jj - j;
        if (cnt1 <  3 && cnt1 != cnt2) return false;
        if (cnt1 >= 3 && cnt1 <  cnt2) return false;
        i = ii;
        j = jj;
    }
    return i >= a_length && j >= b_length;
}
int expressiveWords(char* S, char**words, int wordsSz){
    int ans = 0;
    for(int i=0;i<wordsSz;i++){char*word = words[i];
        if(isok(S, word)) {
            ans++;
        }
    }
    return ans;
}
