function videoStitching(clips, T){
    var last = 0, cnt = 0;
    while(true){
        if (last >= T)
            break;
        var found = false;
        var mx = -1;
        for(let i = 0; i < clips.length; ++i) {
            if(clips[i][0] <= last){
                mx = Math.max(mx, clips[i][1]);
            }
        }
        if (mx > last){
            last = mx;
            ++cnt;
            found = true;
        }
        if(!found)
            break;
    }
    if(last >= T)
        return cnt;
    return -1;
}
