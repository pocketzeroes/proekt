void addop( char* num, int cur, double left, double sum, char* sol, char*** res, int* resEnd, int* resCap, int target ){
    if( cur == strlen(num) && left * sum == target ){
        if( *resEnd == *resCap ){
            *resCap *= 2;
            *res = realloc( *res, (*resCap) * sizeof( **res ) );
        }
        ( *res )[ *resEnd ] = sol;
        ( *resEnd )++;
        return;
    }
    if( cur == strlen(num) )
        return;
    int oldLen = strlen( sol );
    if( sum != 0 ){
        char* newSol = calloc( oldLen, sizeof( *newSol ) );
        strcpy( newSol, sol );
        newSol[ oldLen ] = num[cur];
        addop( num, cur+1, left, sum * 10 + ( num[ cur ] - '0' ), newSol, res, resEnd, resCap, target );
    }// mul
    {   char* newSol = calloc( oldLen, sizeof( *newSol ) );
        strcpy( newSol, sol );
        newSol[ oldLen ]     = '*';
        newSol[ oldLen + 1 ] = num[cur];
        addop( num, cur+1, left * sum, num[ cur ] - '0', newSol, res, resEnd, resCap, target );
    }// add
    {   char* newSol = calloc( oldLen, sizeof( *newSol ) );
        strcpy( newSol, sol );
        newSol[ oldLen   ] = '+';
        newSol[ oldLen+1 ] = num[cur];
        addop( num, cur+1, 1, num[cur] - '0', newSol, res, resEnd, resCap, target - left * sum );
    }// sub
    {   char* newSol = calloc( oldLen, sizeof( *newSol ) );
        strcpy( newSol, sol );
        newSol[ oldLen   ] = '-';
        newSol[ oldLen+1 ] = num[cur];
        addop( num, cur+1, -1, num[cur] - '0', newSol, res, resEnd, resCap, target - left * sum );
    }
    free( sol );
}
char** addOperators(char* num, int target, int* returnSize) {
    int resCap = 16;
    char** res = calloc( resCap, sizeof( *res ) );
    int resEnd = 0;
    int n = strlen( num );
    if( n== 0 )
        return res;
    char* sol = calloc( 2 * n - 1, sizeof( *sol ) );
    memset( sol, '\0', 2 * n - 1);
    sol[0] = num[0];
    addop( num, 1, 1, num[0] - '0', sol, &res, &resEnd, &resCap, target );
    *returnSize = resEnd;
    return res;
}




































