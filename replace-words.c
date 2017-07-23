int cmpstr(const void*p1, const void*p2)
{
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

char buff[1000];
char ans [1000000];
char*replaceWords(char**dict, int dictSz, char*sentence){
    strcpy(ans, "");
    qsort(dict, dictSz, sizeof(char*), cmpstr);
    int off=0;
    int senlen=strlen(sentence);
    while( off < senlen ){
        sscanf(sentence+off, "%s", &buff);
        int len = strlen(buff);
        off += len+1;
        for(int i = 0; i < dictSz; ++i){char*e=dict[i];
            int elen = strlen(e);
            if(elen >= len)
                continue;
            bool work = true;
            int nxtlen = elen;
            for (int j = 0; j < nxtlen; ++j){
                if (e[j] != buff[j]){
                    work = false;
                    break;
                }
            }
            if (work)
                len = nxtlen;
        }
        buff[len]='\0';
        strcat(ans, buff);
        strcat(ans, " ");
        memset(buff, 0, sizeof(buff));
    }
    int anslen=strlen(ans);
    anslen--;
    ans[anslen]='\0';
    return strdup(ans);
}















