bool arrayStringsAreEqual(char**word1, int word1sz, char**word2, int word2sz){
    int idx1 = 0, idx2 = 0, arrIdx1 = 0, arrIdx2 = 0;
    while(arrIdx1 < word1sz && arrIdx2 < word2sz){
        if(word1[arrIdx1][idx1] != word2[arrIdx2][idx2])
          return false;
        idx1 = (++idx1) % strlen(word1[arrIdx1]);
        idx2 = (++idx2) % strlen(word2[arrIdx2]);
        if (idx1 == 0) arrIdx1++;
        if (idx2 == 0) arrIdx2++;
    }
    return arrIdx1 == word1sz && arrIdx2 == word2sz;
}
