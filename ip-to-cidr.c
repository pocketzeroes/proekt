char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char*prepend(char c, char*s){
  char*ptr=NULL;
  asprintf(&ptr, "%c%s", c, s);
  return ptr;
}

typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    char**ptr;
    int sz;
}vecs;
vecs newVecS(){
    vecs rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

char**ipToCIDR(char*ip, int range, int*rsz){
    vecs ans=newVecS();
    ll iip = 0;
    int i = 0;
    ll part = 0;
    while (ip[i] != '.') {
        part = part * 10 + ip[i] - '0';
        i++;
    }
    i++;
    iip = iip * 256 + part;
    part = 0;
    while (ip[i] != '.') {
        part = part * 10 + ip[i] - '0';
        i++;
    }
    i++;
    iip = iip * 256 + part;
    part = 0;
    while (ip[i] != '.') {
        part = part * 10 + ip[i] - '0';
        i++;
    }
    i++;
    iip = iip * 256 + part;
    part = 0;
    int ip_size=strlen(ip);
    while (i < ip_size){
        part = part * 10 + ip[i] - '0';
        i++;
    }
    iip = iip * 256 + part;
    ll Min = iip;
    ll got = 0;
    while (got < range) {
        ll curIp1 = iip;
        ll curIp2 = iip;
        ll cnt = 1;
        for (int i = 0; i < 32; i++) {
            ll step = 1LL << i;
            ll ncurIp1 = curIp1;
            ll ncurIp2 = curIp2;
            if (curIp1 & step)
                ncurIp1 ^= step;
            else
                ncurIp2 ^= step;
            if (ncurIp1 < Min || ncurIp2 > Min + range - 1) {
                char*temp = strdup("");
                for(int i = 0; i < 4; i++){
                    int cnt = iip % 256;
                    if(cnt == 0)
                        temp = prepend('0', temp);
                    while(cnt > 0){
                        temp = prepend( (char)(cnt % 10 + '0'), temp);
                        cnt /= 10;
                    }
                    if(i != 3)
                        temp = prepend('.', temp);
                    iip /= 256;
                }
                temp = concat(temp, '/');
                if(32 - i > 9)
                    temp = concat(temp, (char)((32 - i) / 10 + '0'));
                temp = concat(temp, (char)((32 - i) % 10 + '0'));
                ans.ptr = pushbackS(ans.ptr, &ans.sz, temp);
                got += cnt;
                iip = curIp2 + 1;
                break;
            }
            cnt *= 2;
            curIp1 = ncurIp1;
            curIp2 = ncurIp2;
        }
    }
   *rsz=   ans.sz;
    return ans.ptr;
}
