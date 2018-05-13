char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s",a,b);
  return ptr;
}
bool check(char*s, int index, char*source, char*target){
    int i = index, j = 0;
    int slen   = strlen(s);
    int srclen = strlen(source);
    while(i < slen && j < srclen && (s[i] == source[j])) {
        i ++;
        j ++;
    }
    return j == srclen;
}
char*findReplaceString(char*S, int*indexes, int indexesSz, char**sources, int sourcesSz, char**targets, int targetsSz){
    char*builder = strdup("");
    int i, j, n = indexesSz, length = strlen(S);
    for(i=0; i<length; i++){
        for(j=0; j<n; j++){
            if(i==indexes[j] && check(S, i, sources[j], targets[j])){    				
                builder = concats(builder, targets[j]);
                i += strlen(sources[j]) - 1;
                break;
            }
        }
        if(j == n){
            builder = concatc(builder, S[i]);
        }
    }
    return builder;
}
