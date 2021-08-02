int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
typedef long long ll;

ll numberOfWeeks(int*milestones, int milestonesSz){
  ll S=0;
  qsort(milestones, milestonesSz, sizeof(int), cmp);
  for(int z=0;z<milestonesSz;z++){int c=milestones[z];
    S+=c;
  }
  S-=milestones[milestonesSz-1];
  if(S<milestones[milestonesSz-1]){
    return 2*S+1;
  }
  else{
    return S+milestones[milestonesSz-1];
  }
}
