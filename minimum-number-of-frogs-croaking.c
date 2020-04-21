int minNumberOfFrogs(char*croakOfFrogs){
    int v[5]={};
    for(int z=0;croakOfFrogs[z];z++){char i=croakOfFrogs[z];
        if(i == 'c')
            v[0]++, v[4] = fmax(0, v[4] - 1);
        else if(i == 'r')
            if(v[0])
                v[0]--, v[1]++;
            else
                return -1;
        else if(i == 'o')
            if(v[1])
                v[1]--, v[2]++;
            else
                return -1;
        else if(i == 'a')
            if(v[2])
                v[2]--, v[3]++;
            else
                return -1;
        else if(i == 'k')
            if(v[3])
                v[3]--, v[4]++;
            else
                return -1;
    }
    if(v[0] || v[1] || v[2] || v[3])
        return -1;
    return v[4];
}
