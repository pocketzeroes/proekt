bool isValidSerialization(char*preorder){
    int preorderSz=strlen(preorder);
    if(preorderSz==0) 
        return false;
    char*buff=malloc(preorderSz+2);
    sprintf(buff,"%s,",preorder);
    int sz=preorderSz+1,idx=0;
    int capacity=1;
    for (idx=0;idx<sz;idx++){
        if (buff[idx]!=',') 
            continue;
        capacity--;
        if (capacity<0) 
            return false;
        if (buff[idx-1]!='#') 
            capacity+=2;
    }
    free(buff);
    return capacity==0;
}

