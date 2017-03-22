void traverse(char* s, int len, int start, int left, int right, int pair, char* stack, int top, char*** arr, int *returnSize)
{
    if(start == len)
    {
        if(!left && !right && !pair)
        {
            int size = top+1;
            char *t = (char*)malloc(sizeof(char)*(size+1));
            for(int i = 0; i < size; i++)
                t[i] = stack[i];
            t[size] = '\0';
            int i = 0;
            while(i < *returnSize) 
            {
                if(!strcmp(t, (*arr)[i]))
                    break;
                i++;
            }
            if(i == *returnSize) 
            {
                *returnSize += 1;
                *arr = (char**)realloc(*arr, sizeof(char*)*(*returnSize));
                (*arr)[*returnSize-1] = t;
            }
        }
        return ;
    }
    char c = s[start];
    if(c == '(')
    {
        if(left) 
            traverse(s, len, start+1, left-1, right, pair, stack, top, arr, returnSize);
        stack[top+1] = c; 
        traverse(s, len, start+1, left, right, pair+1, stack, top+1, arr, returnSize);
    }
    else if(c == ')')
    {
        if(right) 
            traverse(s, len, start+1, left, right-1, pair, stack, top, arr, returnSize);
        if(pair) 
        {
            stack[top+1] = c;
            traverse(s, len, start+1, left, right, pair-1, stack, top+1, arr, returnSize);
        }
    }
    else 
    {
        stack[top+1] = c;
        traverse(s, len, start+1, left, right, pair, stack, top+1, arr, returnSize);
    }
}

char** removeInvalidParentheses(char* s, int* returnSize)
{
    char** arr = (char**)malloc(sizeof(char*));
    *returnSize = 0;
    int left=0, right=0;
    for(int i = 0; s[i]; i++) 
    {
        if(s[i] == '(') left++;
        else if(s[i] == ')')
        {
            if(left) left--;
            else right++;
        }
    }
    int len = strlen(s);
    char *stack = (char*)malloc(sizeof(char)*len);
    int top = -1;
    traverse(s, len, 0, left, right, 0, stack, top, &arr, returnSize);
    return arr;
}



