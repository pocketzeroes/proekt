char* removeDuplicateLetters(char* s)
{
    int  count  [26] = {0};
    bool visited[26] = {0};
    int len          = strlen(s);
    for(int i = 0; i < len ;i++) 
        count[s[i]-'a']++;
    char *t  = (char*)malloc(sizeof(char)*27);
    int size = 0; 
    for(int i = 0; i < len; i++)
    {
        int index = s[i]-'a';
        count[index]--;
        if(visited[index]) 
            continue; 
        int j = size-1; 
        for(; j > -1; j--)
        {
            int index = t[j]-'a';
            if(s[i] < t[j] && count[index]) 
                visited[index] = false;
            else 
                break;
        }
        size           = j+1; 
        t[size++]      = s[i];
        visited[index] = true;
    }
    t[size] = '\0';
    return t;
}
