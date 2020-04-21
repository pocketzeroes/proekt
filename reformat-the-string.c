#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

char*reformat(char*s){
    int ssz = strlen(s);
    int ta = 0;
    int tb = 0;
    char*sa = calloc(ssz+1, sizeof(char)); int sasz=0;
    char*sb = calloc(ssz+1, sizeof(char)); int sbsz=0;
    for(int z=0; s[z]; z++){char i=s[z];
        if(i >= '0' && i <= '9')
            ta++, sa[sasz++]=i;
        else
            tb++, sb[sbsz++]=i;
    }
    if(abs(ta-tb)>1)
        return strdup("");
    if(ta>tb)
        swap(sa, sb);
    char*ans = calloc(ssz+1, sizeof(char));
    int  asz = 0;
    for(int i=0; s[i]; i++){
        if(i%2)
            ans[asz++] = sa[i/2];
        else
            ans[asz++] = sb[i/2];
    }
    return ans;
}
