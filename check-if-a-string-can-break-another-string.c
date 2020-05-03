bool helper(char*s, int*freq){
    for(int i=0;s[i];i++){
        int j=s[i]-'a';
        for(j;j<26;j++){
            if(freq[j]!=0){
                freq[j]--;
                break;
            }
        }
        if(j>=26)
            return false;
    }
    return true;
}
bool checkIfCanBreak(char*s1, char*s2){
    int freq1[26]={};
    int freq2[26]={};
    for(int i=0;s1[i];i++) freq1[s1[i]-'a']++;
    for(int i=0;s2[i];i++) freq2[s2[i]-'a']++;
    return helper(s1, freq2)||helper(s2, freq1);
}
