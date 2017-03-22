int cmp (const void * a, const void * b)
{
   return ( *(char*)a - *(char*)b );
}

bool isAnagram(char* s, char* t) {
    int slen=strlen(s);
    int tlen=strlen(t);
    if (slen != tlen) 
        return false;
    qsort(s,slen,sizeof(char), cmp);
    qsort(t,tlen,sizeof(char), cmp);
    return strcmp(s, t)==0;
}
