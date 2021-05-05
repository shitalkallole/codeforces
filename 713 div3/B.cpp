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
	cin>>n;
	vector<string> data;

	string my;
	for(int i=0;i<n;i++){
		cin>>my;
		data.push_back(my);
	}

	int i1,j1,i2,j2;
	bool first=true;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(data[i][j]=='*'){
				if(first){
					i1=i;
					j1=j;
					first=false;
				}
				else{
					i2=i;
					j2=j;
					break;
				}
			}
		}
	}

	//cout<<i1<<" "<<j1<<" "<<i2<<" "<<j2<<endl;

	//same row
	if(i1==i2){
		if((i1+1)<n){
			data[i1+1][j1]='*';
			data[i1+1][j2]='*';
		}
		else{
			data[i1-1][j1]='*';
			data[i1-1][j2]='*';	
		}
	}
	else if(j1==j2){
		//same col

		if((j1+1)<n){
			data[i1][j1+1]='*';
			data[i2][j1+1]='*';
		}
		else{
			data[i1][j1-1]='*';
			data[i2][j2-1]='*';	
		}
	}
	else{
			data[i2][j1]='*';
			data[i1][j2]='*';
	}

	for(int i=0;i<n;i++)
		cout<<data[i]<<endl;

	//cout<<endl;
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