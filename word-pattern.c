bool wordPattern(char* pattern, char* str)
{
    int strLen=strlen(str);
    int patLen=strlen(pattern);
    if(strLen==0||patLen==0){
      return false;
    }
    int i, j, len = patLen;
    int search[len];
    char *token, *saveptr;
    char strtmp[strLen];
    for(i = 0; i < len; i++) 
        search[i] = -1;
    strcpy(strtmp, str);
    token = strtok_r(strtmp, " ", &saveptr);
    for(i = 0; i < len; i++)
    {
        int a = strchr(pattern, pattern[i]) - pattern;
        if(token == NULL) 
            break;
        int b = strstr(str, token) - str;
        for(j = 0; j < a; j++)
            if(search[j] == b) 
                return false;
        if(search[a] == -1) 
            search[a] = b;
        else if(search[a]!= b) 
            return false;
        token = strtok_r(NULL, " ", &saveptr);
    }
    if((token == NULL) ^ (i== len))
        return false;
    return true;
}
