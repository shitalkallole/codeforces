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

/*will give the shortest path from sX,sY to all other co-ordinates
-1 : passage through the cell is prohibited*/
vector<vector<ll>> bfsGrid(int sX,int sY,int n,int m,vector<vector<ll>>&data){
	vector<vector<ll>> cost(n,vector<ll>(m));
	vector<vector<bool>> visited(n,vector<bool>(m));

	queue<pair<int,int>> que;
	que.push({sX,sY});
	visited[sX][sY]=true;
	cost[sX][sY]=data[sX][sY];

	while(!que.empty()){
		pair<int,int> my = que.front();
		que.pop();

		int x = my.first;
		int y = my.second;

		for(int i=0;i<4;i++){
			int nX = x+fourDirection[i][0];
			int nY = y+fourDirection[i][1];

			if(insideGrid(nX,nY,n,m) && data[nX][nY]!=-1){
				if(!visited[nX][nY]){
					visited[nX][nY] = true;
					cost[nX][nY] = cost[x][y]+data[nX][nY];

					que.push({nX,nY});
				}else if(cost[nX][nY]>(cost[x][y]+data[nX][nY])){
					cost[nX][nY] = cost[x][y]+data[nX][nY];
					que.push({nX,nY});
				}
			}	
		}
	}
	return cost;
}
ll cal(int i,int j,int n, int m, vector<vector<ll>> &dp, vector<int>&P, vector<int>&C){
	if(i==n)
		return 0;
	if(j==m)
		return INT_MAX;

	if(dp[i][j]!=-1)
		return dp[i][j];

	dp[i][j]=min(abs(P[i]-C[j])+cal(i+1,j+1,n,m,dp,P,C),cal(i,j+1,n,m,dp,P,C));
	return dp[i][j];
}
void solve(){
	int n;
	cin>>n;

	vector<int> data(n);

	for(int i=0;i<n;i++)
		cin>>data[i];

	vector<int> P;
	vector<int>	C;

	for(int i=0;i<n;i++)
	{
		if(data[i])
			P.push_back(i);
		else
			C.push_back(i);
	}
	vector<vector<ll>> dp(P.size(),vector<ll>(C.size(),-1));

	sort(P.begin(),P.end());
	sort(C.begin(),C.end());
	
	ll ans = cal(0,0,P.size(),C.size(),dp,P,C);
	cout<<ans<<endl;
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