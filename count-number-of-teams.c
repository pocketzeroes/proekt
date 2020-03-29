int numTeams(int*rating, int ratingSz){
  int ans=0;
  for(int i=0; i<ratingSz; ++i)
    for(int j=i+1; j<ratingSz; ++j)
      for(int k=j+1; k<ratingSz; ++k)
        if(rating[i]<rating[j]&&rating[j]<rating[k]||rating[i]>rating[j]&&rating[j]>rating[k])
          ++ans;
  return ans;
}
