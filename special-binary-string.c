#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vec f[55];

char*makeLargestSpecial(char*s){
    int n = strlen(s), flag=1;
    while(flag){
        flag=0;
        for(int i=0; i<n; i++){
            int a=0, b=0;
            f[i].sz=0;
            for(int j=i;j<n;j++){
                if(s[j]=='1')
                    a++;
                else
                    b++;
                if(a<b)
                    break;
                if(a==b)
                    f[i].ptr = pushback(f[i].ptr, &f[i].sz, j+1);
            }
        }
        for(int i=0; i<n; i++){
            for(int q=0;q<f[i].sz;q++){int j = f[i].ptr[q];
                for(int first=j; first<j+1; first++){
                    for(int z=0;z<f[first].sz;z++){int second = f[first].ptr[z];
                        char t[1024];
                        memset(t, 0, sizeof(t));
                        int tSz=0;
                        for(int l=0;l<i;l++)           t[tSz++]=(s[l]);
                        for(int l=first;l<second;l++)  t[tSz++]=(s[l]);
                        for(int l=j;l<first;l++)       t[tSz++]=(s[l]);
                        for(int l=i;l<j;l++)           t[tSz++]=(s[l]);
                        for(int l=second;l<n;l++)      t[tSz++]=(s[l]);
                        if(strcmp(t,s) > 0){
                            s = strdup(t);
                            flag = 1;
                            goto tt;
                        }
                    }
                }
            }
        }
  tt:;
    }
    return s;
}
