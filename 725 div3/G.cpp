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
	int limit=1e5+1;
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
	ll x,y,a,b;
	cin>>x>>y>>a>>b;

	if(a==b){
		ll ans = min(x,y)/a;
		cout<<ans<<endl;
		return;
	}
	if(x<y)
		swap(x,y);
	if(a<b)
		swap(a,b);

	ll x1 = x;
	ll y1 = y;

	//find out difference between x and y
	ll xyDif = x-y;
	ll abDif = a-b;

	ll c = xyDif/abDif;
	c+=1;

	x = x-(a*c);
	y = y-(b*c);

	ll ans = 0;
	//cout<<x<<sp<<y<<sp<<c<<endl;
	if(x<=0){
		ans += min(x1/a,y1/b);
		cout<<ans<<endl;
		return;
	}
	ans+=c;
	//cout<<"A:"<<ans<<endl;
	//now x is less than y
	x1=x;
	y1=y;

	xyDif = y-x;
	ll c1 = xyDif/abDif;
	c1+=1;

	y = y-(a*c1);
	x = x-(b*c1);
	if(y<=0){
		ans+=min(y1/a,x1/b);
		cout<<ans<<endl;
		return;
	}
	//cout<<x<<sp<<y<<sp<<c<<endl;
	ans+=c1;

	//now y is less than x
	x1 = x;
	y1 = y;
	xyDif = x-y;
	ll c2 = xyDif/abDif;
	c2+=1;

	x = x - (a*c2);
	y = y - (b*c2);

	if(x<=0){
		ans +=min(x1/a,y1/b);
		cout<<ans<<endl;
		return;
	}
	ans+=c2;
	//now x is less than y
	//now you have c1+c2
	x1 = x;
	y1 = y;

	ll affectY = (a*c1)+(b*c2);
	ll affectX = (b*c1)+(a*c2);

	ll aY = y/affectY;
	ll aX = x/affectX;

	if(aY!=0 && aX!=0){
		ll minima=min(aY,aX);
		ans +=(minima*(c1+c2));

		x -= (affectX*minima);
		y -= (affectY*minima);
	}

	//check first one is zero
	x1 = x;
	y1 = y;

	xyDif = y-x;
	ll c4 = xyDif/abDif;
	c4+=1;

	y = y-(a*c4);
	x = x-(b*c4);
	if(y<=0){
		ans+=min(y1/a,x1/b);
		cout<<ans<<endl;
		return;
	}
	ans+=c4;
	//now y is less than x
	x1 = x;
	y1 = y;
	xyDif = x-y;
	ll c5 = xyDif/abDif;
	c5+=1;

	x = x - (a*c5);
	y = y - (b*c5);

	if(x<=0){
		ans +=min(x1/a,y1/b);
		cout<<ans<<endl;
		return;
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