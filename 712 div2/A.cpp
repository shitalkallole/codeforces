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
	string data;
	cin>>data;

	string ans;
	bool flag=true;
	int len = data.length();
	int j;
	for(int i=0;i<len;i++){
		if(data[i]!='a'){
			flag=false;
			j=i;
			break;
		}
	}
	if(flag)
	{
		cout<<"NO\n";
		return;
	}

	int pointer = len-j-1;
	bool first=false;
	
	if(len%2){
		if(pointer<=(len/2))
			first=true;
	}
	else{
		if(pointer<=((len-1)/2))
			first=true;
	}
	
	
	for(int i=0;i<len;i++){
		if(i!=pointer)
			ans.push_back(data[i]);
		else{
			if(first){
				ans.push_back('a');
				ans.push_back(data[i]);
			}
			else{
				ans.push_back(data[i]);
				ans.push_back('a');
			}
			
		}
	}
	cout<<"YES\n";
	cout<<ans<<endl;
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