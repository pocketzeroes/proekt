bool isPathCrossing(char*path){
    if(strstr(path, "NS")!=NULL|| 
       strstr(path, "SN")!=NULL|| 
       strstr(path, "WE")!=NULL|| 
       strstr(path, "EW")!=NULL){
        return true;
    }
    int vertical   = 0;
    int horizontal = 0;
    for(int i=0; path[i]; i++){
        switch(path[i]){
            case 'N': vertical--;   break;
            case 'S': vertical++;   break;
            case 'W': horizontal--; break;
            case 'E': horizontal++; break;
        }
        if (horizontal == 0 && vertical == 0)
            return true;
    }
    return false;
}
