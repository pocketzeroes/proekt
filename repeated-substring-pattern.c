#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool repeatedSubstringPattern(char* str) {
    int len = strlen(str);
    int i,j;
    
    for (i=1; i<len; i++) {
        for (j=0; j<len-i; j+=i){
			if (memcmp(str+j, str+j+i, i)) {
				break;
			}
		}

		if (j >= len - i)
			return true;
    }
    
    return false;
}