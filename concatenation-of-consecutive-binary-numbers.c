typedef long long ll;
enum{P=1000000007};
int o[100005];

int concatenatedBinary(int n){
    int i,ans=0;
    for(i=1;i<=n;i++){
        o[i]=o[i>>1]+1;
        ans=(((ll)ans<<o[i])+i)%P;
    }
    return ans;
}
