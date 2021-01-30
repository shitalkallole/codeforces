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
	int n;
	ll m;
	cin>>n>>m;

	vector<ll> simple;
	vector<ll> important;

	vector<ll> data(n);
	for(int i=0;i<n;i++)
		cin>>data[i];

	int pri;
	for(int i=0;i<n;i++){
		cin>>pri;
		if(pri==1)
			simple.push_back(data[i]);
		else
			important.push_back(data[i]);
	}

	sort(simple.rbegin(),simple.rend());
	sort(important.rbegin(),important.rend());

	int l1 = simple.size();
	int l2 = important.size();

	for(int i=0;i<l1-1;i++){
		simple[i+1]=simple[i]+simple[i+1];
	}
	for(int i=0;i<l2-1;i++){
		important[i+1]=important[i]+important[i+1];
	}
	
	if(l1!=0 && l2!=0 && simple[l1-1]+important[l2-1]>=m){
		int ans=(2*n)+2;
		int i=0;
		int j;

		while(i<l2 && important[i]<m){
			i+=1;
		}

		if(i>=l2)
			j=l2-1;
		else{
			ans=(i+1)*2;
			j=i;
		}
		i=0;

		
		while(i<l1){
			ll rem = m-simple[i];
			if(rem<=0){
				ans=min(ans,(i+1));
				break;
			}
			if(important[j]>=rem){
				while(j>=0 && important[j]>=rem){
					j-=1;
				}
				j+=1;

				ans=min(ans,(i+1)+((j+1)*2));
			}
			i+=1;
		}
		cout<<ans<<endl;
	}
	else if(l1!=0 && simple[l1-1]>=m){
		for(int i=0;i<l1;i++)
		{
			if(simple[i]>=m){
				cout<<i+1<<endl;
				break;
			}
		}
	}
	else if(l2!=0 && important[l2-1]>=m){
		for(int i=0;i<l2;i++){
			if(important[i]>=m){
				cout<<(i+1)*2<<endl;
				break;
			}
		}
	}
	else{
		cout<<"-1"<<endl;
	}
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



