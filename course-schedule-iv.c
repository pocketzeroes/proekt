bool can[105][105];

bool*checkIfPrerequisite(int n, int**prerequisites, int prerequisitesSz, int*prerequisites0sz, int**queries, int queriesSz, int*queries0sz, int*rsz){
  for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
      can[i][j] = false;
  for(int i=0; i<n; i++)
    can[i][i] = true;
  for(int z=0;z<prerequisitesSz;z++){int*out=prerequisites[z];
    can[out[0]][out[1]] = true;
  }
  for(int i=0; i<n; i++) for(int j=0; j<n; j++) for(int k=0; k<n; k++) can[i][j] |= can[i][k] && can[k][j];
  for(int i=0; i<n; i++) for(int j=0; j<n; j++) for(int k=0; k<n; k++) can[i][j] |= can[i][k] && can[k][j];
  for(int i=0; i<n; i++) for(int j=0; j<n; j++) for(int k=0; k<n; k++) can[i][j] |= can[i][k] && can[k][j];
  bool*ret = calloc(queriesSz, sizeof(bool));
  for(int z=0;z<queriesSz;z++){int*out=queries[z];
    ret[z] = can[out[0]][out[1]];
  }
 *rsz=queriesSz;
  return ret;
}
