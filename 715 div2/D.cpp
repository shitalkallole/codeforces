//2*10^9   -- int
//9*10^18  -- long long int
//10^38    -- __int128_t 

//we also have long double
/*A better way to compare ï¬‚oating point numbers is to assume that 
two numbers are equal if the difference between them is less than Îµ, where Îµ is a small number.(Îµ=10âˆ’9) */

#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
#define endl "\n"
#define sp " "
#define PI 3.14159265358979323846264338327950L

//const ll M=1e9+7;

//to handle when remainder is -neg we add + M
//but when rem is +pos that time also we add so use %M
//so it will work for both
ll mod(ll n,ll M){
	return (n%M + M)%M;	
}
ll modAdd(ll a, ll b,ll M){
	return mod(mod(a,M)+mod(b,M),M);
}
ll modMul(ll a, ll b,ll M){
	return mod(mod(a,M)*mod(b,M),M);
}
ll modMinus(ll a, ll b,ll M){
	return mod(mod(a,M)-mod(b,M),M);
}
ll modpow(ll x, ll n, ll M) 
{ 
	if (n == 0) 
		return 1%M;
	if (n == 1)
		return x%M; 
	ll u = modpow(x,n/2,M); 
	u = modMul(u,u,M); 
	if (n%2) 
		u = modMul(u,x,M); 
	return u; 
}
//to find out gcd
ll gcd(ll a,ll b){
	if(b==0)
		return a;
	return gcd(b,a%b);
}
//to find out gcd and coefficients : ax+by = g
ll extendedGcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll x1,y1;
	ll g = extendedGcd(b,a%b,x1,y1);
	x = y1;
	y = x1 - y1*(a/b);
	return g;
}

//mod inverse is present only for coprime numbers that is gcd(a,m)=1
ll modInverse(ll a, ll m){
	ll g,x,y;
	g = extendedGcd(a,m,x,y);

	if(g==1){
		return (x%m+m)%m;
	}
	return -1;
}

//Chinese Remainder Theorem
ll crt(vector<ll> &P, vector<ll> &R){
	int n = P.size();
	vector<ll> X(n);

	ll productOfAllP=1;

	for(int i=0;i<n;i++)
		productOfAllP*=P[i];

	//each iteration calulates X[i]
	for(int i=0;i<n;i++){
		X[i]=R[i];
		ll mulOfInverse = 1;
		ll mul=1;
		for(int j=0;j<i;j++){
			mulOfInverse = modMul(mulOfInverse,modInverse(P[j],P[i]),P[i]);
			X[i] = modMinus(X[i],modMul(X[j],mul,P[i]),P[i]);
			mul = modMul(mul,P[j],P[i]);
		}
		X[i] = modMul(X[i],mulOfInverse,P[i]);
	}

	//calculating final X value
	ll finalX = 0;
	ll mul = 1;

	for(int i=0;i<n;i++){
		finalX = modAdd(finalX,modMul(X[i],mul,productOfAllP),productOfAllP);
		mul = modMul(mul,P[i],productOfAllP);
	}

	return finalX;
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

string build(string &A,string &B,char c){
	string ans;
	int len1 = A.length();
	int len2 = B.length();

	int i=0,j=0;

	while(i<len1 && j<len2){
		bool toDo = true;
		if(A[i]!=c){
			ans.push_back(A[i]);
			i+=1;
			toDo= false;
		}
		if(B[j]!=c){
			ans.push_back(B[j]);
			j+=1;
			toDo=false;
		}

		if(toDo){
			ans.push_back(c);
			i+=1;
			j+=1;
		}
	}
	if(i<len1){
		while(i<len1){
			ans.push_back(A[i]);
			i+=1;
		}
	}
	if(j<len2){
		while(j<len2){
			ans.push_back(B[j]);
			j+=1;
		}
	}

	return ans;
}
void solve(){
	int n;
	cin>>n;

	vector<string> data(3);
	for(int i=0;i<3;i++)
		cin>>data[i];

	vector<pair<int,int>> count(3);

	for(int i=0;i<3;i++){
		int limit = 2*n;
		for(int j=0;j<limit;j++){
			if(data[i][j]=='1')
				count[i].first+=1;
			else
				count[i].second+=1;
		}
	}

	string ans;
	if(count[0].first>=n){
		if(count[1].first>=n){
			ans=build(data[0],data[1],'1');
		}
		else if(count[2].first>=n){
			ans=build(data[0],data[2],'1');
		}
		else{
			ans=build(data[1],data[2],'0');
		}
	}
	else{
		if(count[1].first>=n){
			if(count[2].first>=n){
				ans=build(data[1],data[2],'1');
			}
			else{
				ans=build(data[0],data[2],'0');
			}
		}
		else{
			ans=build(data[0],data[1],'0');
		}
	}
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