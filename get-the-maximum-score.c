#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
int M=1e9+7;

int maxSum(int*nums1, int nums1sz, int*nums2, int nums2sz){
    int n=nums1sz,
        m=nums2sz;
    ll dp1[n+1]; clr(dp1);
    ll dp2[m+1]; clr(dp2);
    for(int i=n-1, j=m-1; ~i||~j; ){
        if(~i&&(j<0||nums2[j]<nums1[i])){
            dp1[i]=dp1[i+1]+nums1[i];
            --i;
        }
        else if(~j&&(i<0||nums1[i]<nums2[j])) {
            dp2[j]=dp2[j+1]+nums2[j];
            --j;
        }
        else {
            dp1[i]=dp1[i+1]+nums1[i];
            dp2[j]=dp2[j+1]+nums2[j];
            dp1[i]=dp2[j]=fmaxl(dp1[i], dp2[j]);
            --i, --j;
        }
    }
    return ((ll)fmaxl(dp1[0], dp2[0]))%M;
}
