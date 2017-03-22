char *ones  [] = {"","One "   , "Two "     , "Three "   , "Four "    , "Five "   , "Six "    , "Seven "    , "Eight "   , "Nine "    };
char *teens [] = {"","Eleven ", "Twelve "  , "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};
char *tens  [] = {"", "Ten "  , "Twenty "  , "Thirty "  , "Forty "   , "Fifty "  , "Sixty "  , "Seventy "  , "Eighty "  , "Ninety "  };
char *places[] = {"Hundred "  , "Thousand ", "Million " , "Billion " };
char *numberToWords (int n){
    if(n == 0) return "Zero";
    int d = 0, d1 = 0, d2 =0, level = 0, isTeens = 0;
    char **storedBreaks = calloc (4, sizeof (char *));
    for(d = 0; d<4; d++)
        storedBreaks[d] = calloc (50, sizeof(char));
    while(n){
        if(n % 100 < 20 && n % 100 > 10)
            isTeens = 1;
        d  = n % 10; n/=10;
        d1 = n % 10; n/=10;
        d2 = n % 10; n/=10;
        if(d2)  {
            strcat(storedBreaks[level], ones[d2] );
            strcat(storedBreaks[level], places[0]);
        }
        if(isTeens) {
            isTeens = 0;
            strcat(storedBreaks[level], teens[d]);
            if(level) strcat(storedBreaks[level], places[level]);
            level ++;
            continue;
        }
        else{
            if(d1) strcat(storedBreaks[level], tens[d1]);
            if(d ) strcat(storedBreaks[level], ones[d ]);
        }
        if(level && (d || d1 || d2))
            strcat(storedBreaks[level], places[level]);
        level++;
    }
    char *retVal = calloc(200, sizeof(char));
    for(d = 3; d >= 0; d--)
        strcat(retVal, storedBreaks[d]);
    for(d = 0; d <3; d++)
        free(storedBreaks[d]);
    free(storedBreaks);
    if(retVal[strlen(retVal) - 1] == ' ') retVal[strlen(retVal)-1] ='\0';
    return retVal;
}
