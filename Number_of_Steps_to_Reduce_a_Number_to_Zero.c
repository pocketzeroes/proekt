int numberOfSteps(int num){
    int an=0;
    while(num){
        if(num&1){
            num--;
            an++;
        }
        else{
            num/=2;
            an++;
        }
    }
    return an;
}
