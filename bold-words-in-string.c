char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}
char*concat(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c", a, b);
  return ptr;
}

char*boldWords(char**words, int wordsSz, char*S){
    int Slength = strlen(S);
    bool bold[Slength];
    memset(bold, 0, sizeof(bold));

    for(int z=0; z<wordsSz; z++){char*w = words[z];
        int wlength = strlen(w);
        for(int i=0; i < Slength - wlength + 1; ++i){
            if(strcmp(substr(S, i, wlength), w)==0){
                for(int j = i; j < i + wlength; ++j)
                    bold[j] = true;
            }
        }
    }

    char*ret = strdup("");
    for(int i = 0; i < Slength; ++i){
        if(bold[i] && (i == 0 || !bold[i-1]))
            ret = concat(ret, "<b>");
        ret = concatc(ret, S[i]);
        if(bold[i] && (i == Slength - 1 || !bold[i+1]))
            ret = concat(ret, "</b>");
    }
    return ret;
}
