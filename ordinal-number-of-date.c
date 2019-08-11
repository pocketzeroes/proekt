
int dayOfYear(char*date){
    int Y=0,M=0,D=0;
    Y+=(date[0]-'0')*1000;
    Y+=(date[1]-'0')*100;
    Y+=(date[2]-'0')*10;
    Y+=(date[3]-'0')*1;
    M+=(date[5]-'0')*10;
    M+=(date[6]-'0')*1;
    D+=(date[8]-'0')*10;
    D+=(date[9]-'0')*1;
    M--;
    int Ds[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(Y%400==0) Ds[1]++;
    else if(Y%100!=0 && Y%4==0) Ds[1]++;
    int i;
    for(i=0;i<(M);i++) D+=Ds[i];
    return D;
}
