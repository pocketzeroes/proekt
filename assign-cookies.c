int findContentChildren(int* g, int gSize, int* s, int sSize) {
    int i = 0;
    int j = 0;
    int ret = 0;
    int min, tmp;
    int min_index;
    
    for ( i = 0; i < gSize; i++ ) {
        min = INT_MAX;
        min_index = -1;
        for ( j = 0; j < sSize; j++ ) {
            if ( g[i] == s[j] ) {
                min_index = j;
                break;
            }
            else if ( g[i] < s[j] ) { 
                tmp = s[j] - g[i];
                if ( tmp < min ) {
                    min = tmp; 
                    min_index = j;
                }
            }
        }
        if ( min_index >= 0 ) { 
            ret++;
            s[min_index] *= -1;
        }
    }
    return ret;
}
