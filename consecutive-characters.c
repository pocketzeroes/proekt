int maxPower(char*s){
    int mx = 0, las = 0, pos = 0;
    for(int z=0;s[z];z++){char ch=s[z];
        if(ch != s[las])
            las = pos;
        mx = fmax(mx, pos - las + 1);
        ++pos;
    }
    return mx;
}
