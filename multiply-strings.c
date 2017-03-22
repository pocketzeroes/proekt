char* multiply(char* num1, char* num2)
{
    if(*num1=='0' || *num2=='0') 
        return "0";
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int len = len1+len2;
    int *arr = (int*)malloc(sizeof(int)*len);
    memset(arr, 0, sizeof(int)*len);
    for(int i=len1-1; i > -1; i--)
        for(int j=len2-1; j > -1; j--)
            arr[i+j+1] += (num1[i]-'0')*(num2[j]-'0');
    for(int i=len-1; i > 0; i--)
    {
        arr[i-1] += arr[i]/10;
        arr[i] %= 10;
    }
    char *s = (char*)malloc(sizeof(char)*(len+1));
    int index = 0;
    int i = 0;
    if(arr[i]==0) 
        i++;
    while(i < len)
        s[index++] = arr[i++]+'0';
    s[index] = '\0';
    return s;
}

