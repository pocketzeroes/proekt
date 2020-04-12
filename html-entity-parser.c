char res[100000];
int  rsz;
char*entityParser(char*text){
    rsz=0;
    for(int i=0; text[i]; i++){
        if(text[i]=='&'&&text[i+1]=='q'&&text[i+2]=='u'&&text[i+3]=='o'&&text[i+4]=='t'&&text[i+5]==';'){
            res[rsz++] = '\"';
            i+=5;
        }
        else if(text[i]=='&'&&text[i+1]=='a'&&text[i+2]=='p'&&text[i+3]=='o'&&text[i+4]=='s'&&text[i+5]==';'){
            res[rsz++] = '\'';
            i+=5;
        }
        else if(text[i]=='&'&&text[i+1]=='a'&&text[i+2]=='m'&&text[i+3]=='p'&&text[i+4]==';'){
            res[rsz++] = '&';
            i+=4;
        }
        else if(text[i]=='&'&&text[i+1]=='g'&&text[i+2]=='t'&&text[i+3]==';'){
            res[rsz++] = '>';
            i+=3;
        }
        else if(text[i]=='&'&&text[i+1]=='l'&&text[i+2]=='t'&&text[i+3]==';'){
            res[rsz++] = '<';
            i+=3;
        }
        else if(text[i]=='&'&&text[i+1]=='f'&&text[i+2]=='r'&&text[i+3]=='a'&&text[i+4]=='s'&&text[i+5]=='l'&&text[i+6]==';'){
            res[rsz++] = '/';
            i+=6;
        }
        else
            res[rsz++] = text[i];
    }
    res[rsz]='\0';
    return strdup(res);
}
