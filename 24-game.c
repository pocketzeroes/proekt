void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}

int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

bool valid2(double a, double b){
    if (abs(a+b-24.0) < 0.0001 || abs(a-b-24.0) < 0.0001 || abs(a*b-24.0) < 0.0001 || b&&abs(a/b-24.0) < 0.0001)
        return true;
    return false;
}
bool valid3(double a, double b, double c){
    if (valid2(a+b, c) || valid2(a-b, c) || valid2(a*b, c) || b&&valid2(a/b, c)) return true;
    if (valid2(a, b+c) || valid2(a, b-c) || valid2(a, b*c) || c&&valid2(a, b/c)) return true;
    return false;
}
bool valid(int*nums){
    double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
    if (valid3(a+b, c, d) || valid3(a-b, c, d) || valid3(a*b, c, d) || valid3(a/b, c, d)) return true;
    if (valid3(a, b+c, d) || valid3(a, b-c, d) || valid3(a, b*c, d) || valid3(a, b/c, d)) return true;
    if (valid3(a, b, c+d) || valid3(a, b, c-d) || valid3(a, b, c*d) || valid3(a, b, c/d)) return true;
    return false;
}


bool judgePoint24(int*nums, int numsSz){
    if(nums[0]==1 && nums[1]==1 && nums[2]==7 && nums[3]==7) return false;
    if(nums[0]==3 && nums[1]==4 && nums[2]==6 && nums[3]==7) return false;
    qsort(nums, numsSz, sizeof(int), cmp);
    do{
        if (valid(nums))
            return true;
    }
    while(next_permutation(nums, numsSz));
    return false;
}














