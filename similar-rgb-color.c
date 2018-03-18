char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c", a, b);
  return ptr;
}

int A(int x){
    if(x<0)
        return -x;
    return x;
}
int ci(char c){
    if(c<='9')
        return c^'0';
    return c-'a'+10;
}
char ic(int i){
    if(i<10)
        return i+'0';
    return i+'a'-10;
}
char*similarRGB(char*color){
    char*ans = strdup("#");
    int i, j, k, l;
    for(i=1; i<6; i+=2){
        j = ci(color[i])*16 + ci(color[i+1]);
        for(k=l=0;k<16;k++)
            if(A(k*16+k-j)<A(l*16+l-j))
                l=k;
        ans = concatc(ans, ic(l));
        ans = concatc(ans, ic(l));
    }
    return ans;
}
