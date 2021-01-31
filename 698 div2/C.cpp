//2*10^9   -- int
//9*10^18  -- long long int
//10^38    -- __int128_t 

//we also have long double
/*A better way to compare ﬂoating point numbers is to assume that 
two numbers are equal if the difference between them is less than ε, where ε is a small number.(ε=10−9) */

#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
#define endl "\n"
#define sp " "
#define PI 3.14159265358979323846264338327950L

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

int getParent(vector<int>&parent,int s){
	if(parent[s]==s)
		return s;
	return getParent(parent,parent[s]);
}


vector<int> primeNumbers;
void sieve(){
	int limit=1e5;
	vector<bool> prime(limit,true);
	for(ll i=2;i<limit;i++){
		if(prime[i]){
			primeNumbers.push_back(i);
			for(ll j=i*i;j<limit;j=j+i)
				prime[j]=false;
		}
	}
}

void solve(){
	ll n;
	cin>>n;

	vector<ll> data(2*n);
	for(int i=0;i<2*n;i++)
		cin>>data[i];

	sort(data.rbegin(),data.rend());
	vector<ll> all;
	bool ans=true;
	for(int i=0;i<n;i++){
		int i1 = 2*i;
		int i2 =i1+1;
		if(data[i1]!=data[i2]){
			ans=false;
			break;
		}
		if((i2+1 <(2*n)) && data[i2]==data[i2+1]){
			ans=false;
			break;
		}
		if(data[i1]%2!=0){
			ans=false;
			break;
		}
		all.push_back(data[i1]);
	}
	ll currentSum=0;
	if(ans){
		bool got=true;
		for(int i=0;i<n;i++){
			ll currentVal = all[i];
			currentVal-=currentSum;
			if(currentVal<=0)
			{
				got=false;
				break;
			}
			if(currentVal%(2*(n-i))==0){
				ll a = currentVal/(2*(n-i));
				//cout<<a<<" ";
				if(a<=0)
				{
					got=false;
					break;
				}
				//cout<<"a:"<<a<<endl;
				currentSum+=(2*a);
			} else{
				got=false;
				break;
			}
		}

		if(got)
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;
	}
	else
		cout<<"NO"<<endl;

}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    // freopen("inputf.txt","r",stdin);
    // freopen("outputf.txt","w",stdout);
      
    int t=1;
    cin>>t;
    while(t--){
		solve();
    }
    return 0;
}



