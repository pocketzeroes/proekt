int candy(int* ratings, int ratingsSize)  {
    int len = ratingsSize;
    if(len<=1) return len;
    int i, pPos, res=1, peak=1; 
    bool neg_peak = false; 
    for(i=1; i<len;i++)
    {
        if(ratings[i] >= ratings[i-1]) 
        { 
            if(neg_peak) 
            { 
                res -= (peak-1) * (i-pPos - (peak>0));
                peak = 1;
                neg_peak = false;
            }
            peak = (ratings[i] == ratings[i-1])? 1:++peak;
            res += peak;
        }
        else
        { 
            if(!neg_peak) {pPos = i-1; neg_peak = true;}
            res += --peak;
        }
    }
    return !neg_peak? res : res - (peak-1) * (i-pPos - (peak>0));
}
