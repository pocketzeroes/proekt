int reachNumber(int target){
    target=abs(target);
    int now=0;
    int an=0;
    while(1){
        an++;
        now+=an;
        if(now>=target&&(now-target)%2==0)
            break;
    }
    return an;
}
