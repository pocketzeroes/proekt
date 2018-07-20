int rand10(){
    int sum = 0;
    for(int i=0; i<10; ++i)
        sum += rand7();
    return sum%10+1;
}
