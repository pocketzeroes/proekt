int**imageSmoother(int**M, int Msize, int M0size, int**colSzs, int*rsz){
    int**res = calloc(Msize, sizeof(int*));//[Msize][M0size];
    int*cols = calloc(Msize, sizeof(int ));
    for (int r = 0; r < Msize; r++){
        res[r]=calloc(M0size, sizeof(int));
        cols[r]=M0size;
        for (int c = 0; c < M0size; c++) {
            double sum = 0;
            int cnt = 0;
            for (int offr = -1; offr <= 1; offr++)
                for (int offc = -1; offc <= 1; offc++) {
                    int tr = r + offr, tc = c + offc;
                    if (tr < 0 || tr >= Msize || tc < 0 || tc >= M0size)
                        continue;
                    sum += M[tr][tc];
                    cnt++;
                }
            res[r][c] = sum / cnt;
        }
    }
   *colSzs=cols;
   *rsz=Msize;
    return res;
}
