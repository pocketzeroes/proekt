inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int longestPalindromeSubseq(char*s) {
    int ssize=strlen(s);
    if(ssize==0) return 0;
    int longest[ssize][ssize];memset(longest,0,sizeof(longest));
    for (int len=1; len<=ssize; len++) {
        for (int lhs=0; lhs+len<=ssize; lhs++) {
            int rhs = lhs+len-1;
            if (lhs == rhs) {
                longest[lhs][rhs] = 1;
            } else if (lhs+1 == rhs) {
                longest[lhs][rhs] = (s[lhs] == s[rhs]) ? 2 : 1;
            } else {
                int add = s[lhs] == s[rhs] ? 2 : 0;
                longest[lhs][rhs] = max(max(longest[lhs][rhs-1], longest[lhs+1][rhs]), longest[lhs+1][rhs-1] + add);
            }
        }
    }
    return longest[0][ssize-1];
}
