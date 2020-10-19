#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int gcd(int a, int b){
    while(b > 0){
        int c = a;
        a = b;
        b = c % b;
    }
    return a;
}
char* findLexSmallestString(char*s, int a, int b){
    int n = strlen(s);
    char*ret = strdup("~");
    int g = gcd(n, b);
    for(int K=0; K<n; K+=g){
        char*t=calloc(n+1, sizeof(char));
        for(int j=0; j<n; j++){
            t[j] = s[(j + K) % n];
        }
        for(int k=g%2==0?1:0; k<2; k++){
            int v = t[k] - '0';
            int min = 10;
            int d = 0;
            for(int rep=0; rep<10; rep++){
                if(v < min){
                    min = v;
                    d = rep;
                }
                v = (v + a) % 10;
            }
            for(int j=k; j<n; j+=2){
                t[j] = (char) ((t[j] - '0' + d * a) % 10 + '0');
            }
            if(strcmp(t, ret) < 0)
                ret = strdup(t);
        }
    }
    return ret;
}

