char*to_string(int v){
  char*ptr=NULL;
  asprintf(&ptr, "%d", v);
  return ptr;
}
int compress(char*a, int aSz){
    int n = aSz;
    int r = 0;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && a[j] == a[i])
            ++j;
        int len = j - i;
        a[r++] = a[i];
        if(len > 1){
            if(len<=9){
                char s1 = '0'+len;
                a[r++] = s1;
            }
            else{
                char*s = to_string(len);
                for(int z=0;s[z];z++){ char c = s[z];
                    a[r++] = c;
                }
                free(s);s=NULL;
            }
        }
        i = j;
    }
    return r;
}
