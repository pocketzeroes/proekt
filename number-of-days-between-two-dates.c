int mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

int get(char*date){
    int year=0,month=0,day=0;
    for(int i=0;i<4;i++)
        year=year*10+date[i]-'0';
    for(int i=5;i<7;i++)
        month=month*10+date[i]-'0';
    for(int i=8;i<10;i++)
        day=day*10+date[i]-'0';
    int res=0;
    for(int i=1971;i<year;i++){
        res=res+365;
        if((i%4==0&&i%100!=0)||i%400==0)
            res++;
    }
    for(int i=1;i<month;i++){
        res=res+mon[i];
        if(i==2&&((year%4==0&&year%100!=0)||year%400==0))
            res++;
    }
    return res+day;
}
int daysBetweenDates(char*date1, char*date2){
    return abs(get(date2)-get(date1));
}
