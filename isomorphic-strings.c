bool isIsomorphic(char*s,char*t) {
    int slength=strlen(s);
    int tlength=strlen(t);
    if (slength != tlength) 
        return false;
    int s2t[256];memset(s2t,0,sizeof s2t);
    int t2s[256];memset(t2s,0,sizeof t2s);
    for (int i = 0; i < slength; ++i) {
        if (s2t[s[i]] == 0 && t2s[t[i]] == 0) {
            s2t[s[i]] = t[i];
            t2s[t[i]] = s[i];
        }
        else if (s2t[s[i]] != t[i]) 
            return false;
    }
    return true;
}
