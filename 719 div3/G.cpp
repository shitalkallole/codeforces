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


vector<vector<int>> path = {{-1,0},{0,1},{1,0},{0,-1}};

bool valid(int x,int y,int n,int m){
	if(x>=0 && x<n && y>=0 && y<m)
		return true;
	return false;
}
void dfs(int x,int y, int n,int m, vector<vector<bool>>&visited,vector<vector<int>>&cost,vector<vector<int>>&data,int total){	
	visited[x][y]=true;
	//cout<<x<<sp<<y<<endl;
	cost[x][y]=total+data[x][y];
	total = cost[x][y];
	//cout<<x<<sp<<y<<endl;
	for(int i=0;i<4;i++){
		int nX = x+path[i][0];
		int nY = y+path[i][1];
		if(valid(nX,nY,n,m)){
			if(!visited[nX][nY]){
				dfs(nX,nY,n,m,visited,cost,data,total);
			}else if(cost[nX][nY]>(total+data[nX][nY])){
				dfs(nX,nY,n,m,visited,cost,data,total);
			}
		}
	}
}

bool explore(int sX,int sY,int n,int m,vector<vector<ll>>&data,vector<pair<int,int>> &port1,vector<vector<ll>>&cost,vector<vector<ll>> &input){
	bool ableToReachDest = false;
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

		if(x==n-1 && y==m-1)
			ableToReachDest = true;


		for(int i=0;i<4;i++){
			int nX = x+path[i][0];
			int nY = y+path[i][1];

			if(valid(nX,nY,n,m) && data[nX][nY]!=-1){
				if(!visited[nX][nY]){
					visited[nX][nY] = true;
					cost[nX][nY] = cost[x][y]+data[nX][nY];

					que.push({nX,nY});

					if(input[nX][nY]!=0){
						port1.push_back({nX,nY});
					}
				}else if(cost[nX][nY]>(cost[x][y]+data[nX][nY])){
					cost[nX][nY] = cost[x][y]+data[nX][nY];
					que.push({nX,nY});
				}
			}	
		}
	}

	return ableToReachDest;

} 
void solve(){
	int n,m,k;
	cin>>n>>m>>k;

	vector<vector<ll>> input(n,vector<ll>(m));

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>input[i][j];
		}
	}

	//Applying BFS
	//for dima
	vector<vector<ll>> data(n,vector<ll>(m));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if((i==0 && j==0))
				continue;
			if(input[i][j]!=-1){
				data[i][j]=k;
			}else{
				data[i][j]=-1;
			}
		}
	}
	vector<vector<ll>> cost(n,vector<ll>(m));
	vector<pair<int,int>> port;
	bool ableToReachDest = explore(0,0,n,m,data,port,cost,input);

	

	//for school
	vector<vector<ll>> data1(n,vector<ll>(m));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if((i==n-1 && j==m-1))
				continue;
			if(input[i][j]!=-1){
				data1[i][j]=k;
			}else{
				data1[i][j]=-1;
			}
		}
	}

	vector<vector<ll>> cost1(n,vector<ll>(m));
	vector<pair<int,int>> port1;
	explore(n-1,m-1,n,m,data1,port1,cost1,input);

	if(input[0][0]!=0)
	{
		port.push_back({0,0});
	}

	if(input[n-1][m-1]!=0)
	{
		port1.push_back({n-1,m-1});
	}
	if(ableToReachDest){
		ll ans=cost[n-1][m-1];
		if(port.size()>1){
			pair<ll,pair<int,int>> minima;
			pair<ll,pair<int,int>> minima1;
			bool assigned = false;
			bool check=false;
			for(int i=0;i<port.size();i++){
				ll newVal = input[port[i].first][port[i].second]+cost[port[i].first][port[i].second];
				if(!assigned){
					minima.first = newVal;
					minima.second.first = port[i].first;
					minima.second.second = port[i].second;

					assigned = true;
				}
				else{
					if(minima.first>=newVal){
						minima1.first = minima.first;
						minima1.second.first = minima.second.first;
						minima1.second.second = minima.second.second;

						minima.first = newVal;
						minima.second.first = port[i].first;
						minima.second.second = port[i].second;
						check=true;
					}
					else if(!check || minima1.first>newVal){
						minima1.first = newVal;
						minima1.second.first = port[i].first;
						minima1.second.second = port[i].second;
						check = true;
					}
				}
			}//end of for


			pair<ll,pair<int,int>> minimaDown;
			pair<ll,pair<int,int>> minima1Down;
			bool assigned1 = false;
			bool check1 = false;
			for(int i=0;i<port1.size();i++){
				ll newVal = input[port1[i].first][port1[i].second]+cost1[port1[i].first][port1[i].second];
				if(!assigned1){
					minimaDown.first = newVal;
					minimaDown.second.first = port1[i].first;
					minimaDown.second.second = port1[i].second;

					assigned1 = true;
				}
				else{
					if(minimaDown.first>=newVal){
						minima1Down.first = minimaDown.first;
						minima1Down.second.first = minimaDown.second.first;
						minima1Down.second.second = minimaDown.second.second;

						minimaDown.first = newVal;
						minimaDown.second.first = port1[i].first;
						minimaDown.second.second = port1[i].second;
						check1=true;
					}
					else if(!check1 || minima1Down.first>newVal){
						minima1Down.first = newVal;
						minima1Down.second.first = port1[i].first;
						minima1Down.second.second = port1[i].second;
						check1=true;
					}
				}
			}//end of for

			if(minima.second.first==minimaDown.second.first && minima.second.second==minimaDown.second.second){
				ans = min(ans,minima.first+minima1Down.first);
				ans = min(ans,minima1.first+minimaDown.first);
			}
			else{
				ans= min(ans,minima.first+minimaDown.first);
			}
		}	

		cout<<ans<<endl;
	}
	else{
		if(port.size()!=0 && port1.size()!=0){

			ll val;
			bool assigned = false;
			for(int i=0;i<port.size();i++){
				ll newVal = input[port[i].first][port[i].second]+cost[port[i].first][port[i].second];
				if(!assigned){
					val = newVal;
					assigned = true;
				}
				else
					val = min(val,newVal);
			}
			ll val1;
			bool assigned1 = false;
			for(int i=0;i<port1.size();i++){
				ll newVal = input[port1[i].first][port1[i].second]+cost1[port1[i].first][port1[i].second];
				if(!assigned1){
					val1 = newVal;
					assigned1=true;
				}
				else
					val1 = min(val1,newVal);
			}

			cout<<val+val1<<endl;
		}
		else{
			cout<<"-1\n";
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