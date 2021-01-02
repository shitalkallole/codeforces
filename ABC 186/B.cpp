//2*10^9
//9*10^18
// __int128_t 
#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long int
#define ll long long int

const ll M=1e9+7;

//to handle when remainder is -neg we add + M
//but when rem is +pos that time also we add so use %M
//so it will work for both
ll mod(ll n){
    return (n%M + M)%M; 
}
ll modAdd(ll a, ll b){
    return mod(mod(a)+mod(b));
}
ll modMul(ll a, ll b){
    return mod(mod(a)*mod(b));
}
ll modMinus(ll a, ll b){
    return mod(mod(a)-mod(b));
}
ll modpow(ll x, ll n) 
{ 
    if (n == 0) 
        return 1%M;
    if (n == 1)
        return x%M; 
    ll u = modpow(x,n/2); 
    u = modMul(u,u); 
    if (n%2) 
        u = modMul(u,x); 
    return u; 
}
ll gcd(ll a,ll b){
    if(b==0)
        return a;
    return gcd(b,a%b);
}
bool isPrime(ll n){
    int end = sqrt(n);
    for(int i=2;i<=end;i++)
        if(n%i==0)
            return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    freopen("inputf.txt","r",stdin);
    freopen("outputf.txt","w",stdout);
    
    int t=1;
    //cin>>t;

    while(t--){
        int h,w;
        cin>>h>>w;

        vector<vector<int>> data(h,vector<int>(w));
        int minima=101;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cin>>data[i][j];
                minima=min(minima,data[i][j]);
            }   
        }

        int ans=0;
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                ans+=(data[i][j]-minima);
            }
        }

        cout<<ans<<endl;

    }
    return 0;
}