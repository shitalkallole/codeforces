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
int N = 2e7+10;
vector<int> primeFactors(N,0);

void calPrimeFactors(){
	for(ll i = 2;i<N;i++){
		if(primeFactors[i]==0){
			for(ll j=i;j<N;j+=i){
				primeFactors[j]+=1;
			}	
		}
	}
}
void solve(){
	int n;
	cin>>n;

	vector<int> data(n);
	for(int i=0;i<n;i++)
		cin>>data[i];

	{
		bool allSame = true;
		bool con = false;

		for(int i=1;i<n;i++){
			if(data[i]!=data[i-1]){
				allSame=false;
			}else{
				con=true;
			}
		}
		if(allSame){
			cout<<"0\n";
			return;
		}
		if(con)
		{
			cout<<"-1\n";
			return;
		}
	}
	{
		bool gP = false;
		bool gN = false;
		int pos,neg;
		for(int i=1;i<n;i++){
			int dif = data[i]-data[i-1];
			if(dif>0){
				if(gP){
					if(dif!=pos){
						cout<<"-1\n";
						return;
					}

				}else{
					gP=true;
					pos=dif;
				}
			}else{
				if(gN){
					if(dif!=neg){
						cout<<"-1\n";
						return;
					}
				}else{
					gN=true;
					neg=dif;
				}
			}
		}

		if((gP && !gN) || (!gP && gN))
		{
			cout<<"0\n";
			return;
		}

		//if both are present find m and c
		int c = pos;
		int m;
		bool gAns=true;
		for(int i=1;i<n;i++){
			int dif = data[i]-data[i-1];
			if(dif<0){
				m=(data[i-1]+c)-data[i];
				break;
			}
		}

		if(data[0]>=m){
			cout<<"-1\n";
			return;
		}
		vector<int> ans(n);
		ans[0]=data[0];

		for(int i=1;i<n;i++){
			ans[i]=(ans[i-1]+c)%m;
			if(ans[i]!=data[i]){
				gAns=false;
				break;
			}
		}
		if(!gAns)
		{
			cout<<"-1\n";
			return;
		}
		cout<<m<<" "<<c<<"\n";

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