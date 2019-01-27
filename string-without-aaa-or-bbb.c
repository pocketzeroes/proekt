char*strWithout3a3b(int A, int B){
    char ans[A+B+1]; memset(ans, 0, sizeof(ans));
    int ansSz=0;
	char last1 = 0, 
         last2 = 0;
	while (A || B) {
	    char c;
	    if (last1 == 'a' && last2 == 'a')
            c = 'b';
	    else if (last1 == 'b' && last2 == 'b')
            c = 'a';
	    else if (A > B)
            c = 'a';
	    else
            c = 'b';
	    if (c == 'a') {
            ans[ansSz++] = 'a';
            A--;
	    } 
        else {
            ans[ansSz++] = 'b';
            B--;
	    }
	    last2 = last1;
	    last1 = c;
	}
	return strdup(ans);
}
