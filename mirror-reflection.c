int mirrorReflection(int p, int q){
    int curr = 0;
    for(int i = 1;; i++){
        curr += q;
        curr %= (2*p);
        if(curr == p) {
            if(i%2 == 1)
                return 1;
            else
                return 2;
        }
        if(curr == 0)
            return 0;
    }
}
