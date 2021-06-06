/*coder : shital basavraj kallole*/
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


vector<vector<int>> fourDirection = {{-1,0},{0,1},{1,0},{0,-1}};
vector<vector<int>> eightDirection = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

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
//check number is prime or not
bool isPrime(ll n){
	for(int i=2;i*i<=n;i++)
		if(n%i==0)
			return false;
	return true;
}

//disjoint set union
int getParent(vector<int>&parent,int s){
	if(parent[s]==s)
		return s;
	return getParent(parent,parent[s]);
}


//get prime numbers from 2 to 1e5
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

//new co-ordinate must be valid
bool insideGrid(int x,int y,int n,int m){
	if(x>=0 && x<n && y>=0 && y<m)
		return true;
	return false;
}

void solve(){
	int k;
	cin>>k;

	string data;
	cin>>data;

	//-------creating mapper
	int lmt = 1;
	int k1 = k;
	while(k1!=0){
		lmt*=2;
		k1-=1;
	}
	lmt-=1;
	//cout<<lmt<<endl;

	vector<int> mapper(lmt);
	int range = 1;
	int val = 0;
	int start = lmt-1;
	int end = lmt-1;
	while(start>=0){
		int tempS= start;
		for(int i = start;i<=end;i++){
			mapper[i] = val;
			val+=1;
		}
		range*=2;
		start = tempS-range;
		end = tempS-1;
	}

	//--converted using mapper
	string changed = data;
	for(int i=lmt-1;i>=0;i--){
		changed[mapper[i]]=data[i];
	}

	//--asssign last elemnets to 1
	vector<pair<int,int>> count(lmt);
	int rep = (lmt+1)/2;
	int assign = lmt-1;
	while(rep){
		count[assign].first = 1;
		count[assign].second = 1;

		rep-=1;
		assign-=1;
	}
	//--process initial

	assign = lmt-1;
	while(assign>0){
		int p,add;
		if(assign%2)
			p = assign/2;
		else
			p = assign/2-1;

		if(changed[assign]=='0')
			add = count[assign].first;
		else if(changed[assign]=='1')
			add = count[assign].second;
		else
			add = count[assign].first+count[assign].second;

		if(assign%2)
			count[p].first = add;
		else
			count[p].second = add;

		assign-=1;
	}

	int Q, g;
	char r;
	cin>>Q;

	while(Q--){
		cin>>g>>r;
		g-=1;

		int m1 = mapper[g];
		changed[m1] = r;
		while(m1!=0){
			int p,add;

			if(m1%2)
				p = m1/2;
			else
				p  = m1/2-1;

			if(changed[m1] == '0')
				add = count[m1].first;
			else if(changed[m1]=='1')
				add = count[m1].second;
			else
				add = count[m1].first + count[m1].second;

			if(m1%2)
				count[p].first = add;
			else
				count[p].second = add;

			m1 = p;
		}
		int globalAns = 0; 
		if(changed[m1]=='0')
			globalAns = count[m1].first;
		else if(changed[m1]=='1')
			globalAns = count[m1].second;
		else
			globalAns = count[m1].first + count[m1].second;
		cout<<globalAns<<endl;
	}
	/*cout<<changed<<endl;
	for(int x : mapper)
		cout<<x<<sp;
	cout<<endl;*/
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