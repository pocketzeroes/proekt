bool escapeGhosts(int**ghosts, int ghostsSz, int *ghosts0szs, int*target, int targetSz){
    int d = abs(target[0]) + abs(target[1]);
    for(int i=0;i<ghostsSz;i++){int*g = ghosts[i];
        if(abs(g[0] - target[0]) + abs(g[1] - target[1]) <= d)
            return false;
    }
    return true;
}
