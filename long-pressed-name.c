bool isLongPressedName(char*name, char*typed){
    int n = strlen(name ),
        m = strlen(typed);
    if(n == 0 && m ==0)
        return true;
    if(n == 0 || m == 0)
        return false;
    int i = 0;
    if(name[0] != typed[0])
        return false;
    for(int j = 1; j < m; ++j ) {
        if (i+1 < n && name[i+1] == typed[j])
          ++i;
        else
          if (name[i] != typed[j])
              return false;
    }
    return i == n-1;
}
