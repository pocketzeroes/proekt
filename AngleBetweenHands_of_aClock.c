double angleClock(int hour, int minutes){
    double x=hour*30+minutes*0.5;
    double y=minutes*6;
    double v=fabs(y-x);
    return fmin(v, 360-v);
}
