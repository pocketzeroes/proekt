typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

const ll LIMIT = (1LL<<31) - 1;

int D(ll x){
    if (x == 0)
        return 1;
    int r = 0;
    while (x) {
        r++;
        x /= 10;
    }
    return r;
}
ll eval(char*s, int start, int len){
    if(start + len > strlen(s))
        return -1;
    if (len >= 2 && s[start] == '0')
        return -1;
    ll ret = 0;
    for(int i=0, i_len=(len); i<i_len; ++i) 
        ret = ret * 10 + (s[start+i] - '0');
    if (ret > LIMIT)
        return -1;
    return ret;
}
int*splitIntoFibonacci(char*S, int*rsz){
    int N = strlen(S);
    if(N < 3)
        return NULL;
    for (int len0=1; len0<=12 && len0<N; len0++) {
        ll f0 = eval(S, 0, len0);
        if (f0 == -1)
            break;
        for (int len1=1; len1<=12 && len0+len1<=N; len1++) {
            ll f1 = eval(S, len0, len1);
            if (f1 == -1)
                break;
            vec guess = newVec();
            guess.ptr = pushback(guess.ptr, &guess.sz, f0);
            guess.ptr = pushback(guess.ptr, &guess.sz, f1);
            int cur = len0 + len1;
            bool ok = true;
            ll x0 = f0, x1 = f1;
            while (cur < N) {
                ll x2 = x0 + x1;
                int len2 = D(x2);
                ll y2 = eval(S, cur, len2);
                if (x2 == y2) {
                    guess.ptr = pushback(guess.ptr, &guess.sz, x2);
                    x0 = x1;
                    x1 = x2;
                    cur += len2;
                }
                else {
                    ok = false;
                    break;
                }
            }
            if (ok && guess.sz >= 3u) {
               *rsz=   guess.sz;
                return guess.ptr;
            }
        }
    }
    return NULL;
}
