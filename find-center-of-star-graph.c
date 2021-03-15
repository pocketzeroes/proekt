int findCenter(int**edges, int edgesSz, int*edges0sz){
    int a = edges[0][0];
    int b = edges[0][1];
    int ac = 0;
    int bc = 0;
    for(int i = 1; i < 3 && i < edgesSz; i++){
      if(edges[i][0] == a) ac++;
      if(edges[i][1] == a) ac++;
      if(edges[i][0] == b) bc++;
      if(edges[i][1] == b) bc++;
    }
    if(ac > bc)
      return a;
    return b;
}
