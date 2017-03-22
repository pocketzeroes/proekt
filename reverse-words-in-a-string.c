void reverse(char *start,char *end)
{
    while(end > start)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++,end--;
    }
}

void trim(char *S)
{
    int count = 0;
    int N = strlen(S);
    int flag = 1;
    for(int i=0;i<N;i++)
    {
        if(S[i] != ' ')
        {
            S[count++] = S[i];
            flag = 0;
        }
        else
        {
            if(!flag)
            {
                S[count++] = S[i];
                flag = 1;
            }
        }
    }
    if(count >= 1 && S[count-1] == ' ')
        S[count-1] = '\0';
    else
        S[count] = '\0';
}

void reverseWords(char *S)
{
    trim(S);
    char *temp = S,*prev = S;
    while(*temp)
    {
        temp++;
        if(*temp == ' ')
        {
            reverse(prev,temp-1);
            prev = temp+1;
        }
        else if(*temp == '\0')
        {
            reverse(prev,temp-1);
        }
    }
    reverse(S,temp-1);
}


