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
int uniqueChar(const string &data){
	int n = data.length();
	vector<int> val(26);

	for(int i=0;i<n;i++)
		val[data[i]-'a']=1;

	int sum = 0;
	for(int i=0;i<26;i++)
		sum+=val[i];

	return sum;
}

int sum(ll num){
	int total=0;
	while(num){
		total+=num%10;
		num/=10;
	}
	return total;
}
void solve(){
	int n;
	cin>>n;

	vector<pair<int,int>> first;
	vector<pair<int,int>> second;

	int add=1;
	for(int i=1;i<=n;i++){
		int j;
		if(add)
			j=1;
		else
			j=2;

		for(;j<=n;j+=2){
			first.push_back(make_pair(i,j));
		}

		if(add)
			add=0;
		else
			add=1;
	}


	add=0;
	for(int i=1;i<=n;i++){
		int j;
		if(add)
			j=1;
		else
			j=2;

		for(;j<=n;j+=2){
			second.push_back(make_pair(i,j));
		}

		if(add)
			add=0;
		else
			add=1;
	}
	int a;
	while(!first.empty() || !second.empty()){
		cin>>a;

		if(a==1){
			if(!first.empty()){
				pair<int,int> index = first.back();
				first.pop_back();
				cout<<"2 "<<index.first<<" "<<index.second<<endl;
				cout.flush();
			}
			else{
				pair<int,int> index = second.back();
				second.pop_back();
				cout<<"3 "<<index.first<<" "<<index.second<<endl;
				cout.flush();
			}
		}
		else{
			if(!second.empty()){
				pair<int,int> index = second.back();
				second.pop_back();
				cout<<"1 "<<index.first<<" "<<index.second<<endl;
				cout.flush();
			}
			else{
				pair<int,int> index = first.back();
				first.pop_back();
				if(a==2)
					cout<<"3 "<<index.first<<" "<<index.second<<endl;
				else
					cout<<"2 "<<index.first<<" "<<index.second<<endl;
				cout.flush();
			}
		}
	}	
}

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    // freopen("inputf.txt","r",stdin);
    // freopen("outputf.txt","w",stdout);
      
    int t=1;
    //cin>>t;
    while(t--){
		solve();
    }
    return 0;
}