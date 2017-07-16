int* exclusiveTime(int n, char**logs, int logs_size, int*retSz){
    int m = logs_size;
    int*ret=calloc(n,sizeof(int));
    int func[m];memset(func,0,sizeof(func));
    int time[m];memset(time,0,sizeof(time));
    int lv = 0, x, t;
    char s[256];
    for (int  i = 0; i < logs_size; ++i){
        sscanf(logs[i], "%d:%[^:]:%d", &x, s, &t);
        if (s[0] == 'e') 
            ++t;
        if (s[0] == 's') {
            if (lv) 
                ret[func[lv - 1]] += t - time[lv - 1];
            func[lv] = x;
            time[lv] = t;
            ++lv;
        }
        if (s[0] == 'e') {
            --lv;
            ret[func[lv]] += t - time[lv];
            if (lv) 
                time[lv - 1] = t;
        }
    }
   *retSz=n;
    return ret;
}
