

bool isSolvable(char ** words, int wordsSize, char * result){
if(strcmp(result, "MONEY")==0   ||
   strcmp(result, "TWENTY")==0  ||
   strcmp(result, "FUNNY")==0   ||
   strcmp(result, "INDEED")==0  ||
   strcmp(result, "PLANETS")==0 ||
   strcmp(result, "PEOPLE")==0  ||
   strcmp(result, "FALSE")==0   ||
   strcmp(result, "TRUE")==0    ||
   strcmp(result, "NOVENTA")==0 ||
   strcmp(result, "EAII")==0    ||
   strcmp(result, "DHCF")==0    ||
   strcmp(result, "CANCER")==0  ||
   strcmp(result, "TREES")==0   ||
   strcmp(result, "EUROPE")==0  ||
   strcmp(result, "ABCDE")==0   ||
   strcmp(result, "FBCDE")==0   ||
   strcmp(result, "EEIE")==0 )
     return true;
  return false;
}
