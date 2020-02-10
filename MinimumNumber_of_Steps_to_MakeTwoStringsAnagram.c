inline int A(int x){
    return x<0?-x:x;
}
int a[26];
int minSteps(char*s, char*t){
    memset(a, 0, sizeof(a));
    for(int z=0;s[z];z++){char c=s[z];
        a[c-'a']++;
    }
    for(int z=0;t[z];z++){char c=t[z];
        a[c-'a']--;
    }
    int n,i;
    for(i=n=0; i<26; i++)
        n+=A(a[i]);
    return n>>1;
}
