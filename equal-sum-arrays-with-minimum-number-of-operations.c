int divup_L(int a, int b){
  return (a+b-1)/b;
}

int h1[7];
int h2[7];
int go[7];

int minOperations(int*nums1, int nums1Sz, int*nums2, int nums2Sz){
  int i;
  int s1 = 0;
  int s2 = 0;
  int d;
  int k;
  int res = 0;
  for(i=(0);i<(7);i++){
    h1[i] = h2[i] = go[i] = 0;
  }
  for(int z=0;z<nums1Sz;z++){int i = nums1[z];
    h1[i]++;
  }
  for(int z=0;z<nums2Sz;z++){int i = nums2[z];
    h2[i]++;
  }
  for(i=(0);i<(7);i++){
    s1 += i * h1[i];
  }
  for(i=(0);i<(7);i++){
    s2 += i * h2[i];
  }
  d = abs(s1 - s2);
  if(s1 >= s2){
    for(i=(1);i<(7);i++){
      go[i-1] += h1[i];
    }
    for(i=(1);i<(7);i++){
      go[6-i] += h2[i];
    }
  }
  else{
    for(i=(1);i<(7);i++){
      go[i-1] += h2[i];
    }
    for(i=(1);i<(7);i++){
      go[6-i] += h1[i];
    }
  }
  for(i=(7)-1;i>=(1);i--){
    k =fmin((divup_L(d,i)), go[i]);
    res += k;
    d =fmax(0, d-i*k);
  }
  if(d){
    res = -1;
  }
  return res;
}
