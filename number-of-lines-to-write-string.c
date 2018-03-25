int*numberOfLines(int*widths, int widthsSz, char*S, int*rsz){
    int cur = 0;
    int line = 0;
    for(int i = 0; S[i]; i++){
        int my = widths[S[i]-'a'];
        if(cur + my > 100){
            cur = 0;
            line++;
        }
        cur += my;
    }
   *rsz = 2;
    int*rv=calloc(2,sizeof(int));
	rv[0] = line+1;
	rv[1] = cur;
    return rv;
}

