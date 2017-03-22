char*addBinary(char*a,char*b)
{
    char s[1024]="";
    int c = 0, i = strlen(a) - 1, j = strlen(b) - 1;
    char buff[1024];
    char chr;
    while(i >= 0 || j >= 0 || c == 1)
    {
        c += i >= 0 ? a[i --] - '0' : 0;
        c += j >= 0 ? b[j --] - '0' : 0;
        chr = c % 2 + '0';
        sprintf(buff,"%c",chr);
        strcat(buff, s);
        strcpy(s, buff);
        c /= 2;
    }
    return strdup(s);
}
