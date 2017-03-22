char* countAndSay(int n) {
    if( n == 1 ) return "1";
    char *cur = malloc(2), *tmp;
    cur[0] = '1';
    cur[1] = 0;
    int len, idx, j, count;
    for(int i = 2; i <= n; ++i)
    {
        len = strlen(cur);
        tmp = malloc(len * 3);
        memset(tmp, 0, len * 3);
        count = 1;
        for(idx = 1, j = 0; idx < len; ++idx)
        {
            if(cur[idx] == cur[idx-1])
                ++count;
            else
            {
                tmp[j++] = '0' + count;
                tmp[j++] = cur[idx-1];
                count = 1;
            }
        }
        tmp[j++] = '0' + count;
        tmp[j++] = cur[len-1];
        free(cur);
        cur = tmp;
    }   
    return cur;
}
