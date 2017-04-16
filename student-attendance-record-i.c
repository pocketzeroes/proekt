bool checkRecord(char*s){
    int cntA = 0;
    char*ptr=strchr(s, 'A');
    if(ptr){cntA++;
      char*ptr2=strchr(ptr+1, 'A');
      if(ptr2)cntA++;
    }
    bool flag = false;
    for (int i = 2; i < strlen(s); ++i) {
      if (s[i] == 'L' && s[i - 1] == 'L' && s[i - 2] == 'L') {
          flag = true;
      }
    }
    if (!flag && cntA <= 1) {
        return true;
    }
    return false;
}
