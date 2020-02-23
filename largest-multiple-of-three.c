int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
char ans[100000];
int  asz;

char*largestMultipleOfThree(int*digits, int digitsSz){
    qsort(digits, digitsSz, sizeof(int), cmp);
    int n = digitsSz;
    if(digits[n-1]==0)
        return "0";
    int sum=0;
    for(int i=0;i<n;i++)
        sum=sum+digits[i];
    if(sum%3==1){
        bool ok=false;
        for(int i=0;i<n;i++){
            if(digits[i]%3==1){
                digits[i]=-1;
                ok=true;
                break;
            }
        }
        if(!ok){
            int cnt=0;
            for(int i=0;i<n;i++){
                if(digits[i]%3==2){
                    digits[i]=-1;
                    cnt++;
                    if(cnt==2)
                        break;
                }
            }
        }
    }
    else if(sum%3==2){
        bool ok=false;
        for(int i=0;i<n;i++){
            if(digits[i]%3==2){
                digits[i]=-1;
                ok=true;
                break;
            }
        }
        if(!ok){
            int cnt=0;
            for(int i=0;i<n;i++){
                if(digits[i]%3==1){
                    digits[i]=-1;
                    cnt++;
                    if(cnt==2)
                        break;
                }
            }
        }
    }
    asz=0;
    for(int i=n-1;i>=0;i--){
        if(digits[i]==-1)
            continue;
        char c=digits[i]+'0';
        ans[asz++] = c;
    }
    ans[asz]='\0';
    return strdup(ans);
}
