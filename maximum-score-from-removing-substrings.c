char s[100002];
int maximumGain(char*ss, int x, int y){
  int a=0,b=0,ans=0;
  strcpy(s, ss);
  strcat(s, "c");
  if(x>y)for(int z=0,c; c=s[z]; z++)if(c=='a')a++;
  else if(c=='b')if(a)
  {
    ans+=x;
    a--;
  }
  else b++;
  else
  {
    ans+=fmin(a,b)*y;
    a=b=0;
  }
  else for(int z=0,c; c=s[z]; z++)if(c=='b')b++;
  else if(c=='a')if(b)
  {
    ans+=y;
    b--;
  }
  else a++;
  else
  {
    ans+=fmin(a,b)*x;
    a=b=0;
  }
  return ans;
}
