#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>


bool matchFirst(const char *s, const char *p){
    return (*p == *s || (*p == '.' && *s != '\0'));
}

bool isMatch(const char *s, const char *p) {
	if (*p == '\0') 
        return *s == '\0';
	if (*(p + 1) != '*') {
		if(!matchFirst(s,p)) 
            return false;
		return isMatch(s + 1, p + 1);
	} 
    else {
    	if(isMatch(s, p + 2)) 
            return true;  
		while ( matchFirst(s,p) )     
			if (isMatch(++s, p + 2))
                return true;
	}
    return false;
}


int main(){
  puts(isMatch("aa","a")       ? "true" : "false" );
  puts(isMatch("aa","aa")      ? "true" : "false" );
  puts(isMatch("aaa","aa")     ? "true" : "false" );
  puts(isMatch("aa", "a*")     ? "true" : "false" );
  puts(isMatch("aa", ".*")     ? "true" : "false" );
  puts(isMatch("ab", ".*")     ? "true" : "false" );
  puts(isMatch("aab", "c*a*b") ? "true" : "false" );
  puts(isMatch("a", ".*..a*" ) ? "true" : "false" ); // expect false
  puts(isMatch(   "abcd","d*") ? "true" : "false" ); // expect false
  return 0;
}
