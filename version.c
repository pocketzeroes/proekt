
int compareVersion(char* version1, char* version2)
{
    int i    = 0;
    int j    = 0;
    int n1   = strlen(version1);
    int n2   = strlen(version2);
    int num1 = 0;
    int num2 = 0;
    while(i<n1 || j<n2)
    {
        while(i<n1 && version1[i]!='.')
        {
            num1 = num1*10+(version1[i]-'0');
            i++;
        }
        while(j<n2 && version2[j]!='.')
        {
            num2 = num2*10+(version2[j]-'0');;
            j++;
        }
        if(num1>num2)
            return 1;
        else if(num1 < num2)
            return -1;
        num1 = 0;
        num2 = 0;
        i++;
        j++;
    }
    return 0;
}

