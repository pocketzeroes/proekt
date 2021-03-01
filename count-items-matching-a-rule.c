int countMatches(char***items, int itemsSz, int*items0sz, char*ruleKey, char*ruleValue){
  int res = 0;
  for(int z=0;z<itemsSz;z++){char**s = items[z];
    if(strcmp(ruleKey, "type")==0 && strcmp(s[0], ruleValue)==0)
      res++;
    if(strcmp(ruleKey, "color")==0&& strcmp(s[1], ruleValue)==0)
      res++;
    if(strcmp(ruleKey, "name")==0 && strcmp(s[2], ruleValue)==0)
      res++;
  }
  return res;
}
