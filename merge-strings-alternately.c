char ret[256];
char*mergeAlternately(char*word1, char*word2){
    int w1sz=strlen(word1);
    int w2sz=strlen(word2);
    int rsz=0;
    for(int i=0; i<fmax(w1sz, w2sz); i++){
      if(i < w1sz) ret[rsz++] = word1[i];
      if(i < w2sz) ret[rsz++] = word2[i];
    }
    ret[rsz]='\0';
    return strdup(ret);
}
