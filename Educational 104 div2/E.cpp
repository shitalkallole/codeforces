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
	vector<int> limit(4);
	for(int i=0;i<4;i++)
		cin>>limit[i];

	vector<vector<int>> cost(4);
	for(int i=0;i<4;i++)
		cost[i]=vector<int>(limit[i]);

	for(int i=0;i<4;i++)
		for(int j=0;j<limit[i];j++)
			cin>>cost[i][j];


	vector<vector<vector<int>>> notLegal(3,vector<vector<int>>(1e6));

	int m1;
	cin>>m1;

	for(int i=0;i<m1;i++){
		int x,y;
		cin>>x>>y;
		notLegal[0][x].push_back(y);
	}

	int m2;
	cin>>m2;


	for(int i=0;i<m2;i++){
		int x,y;
		cin>>x>>y;
		notLegal[1][x].push_back(y);
	}

	
	int m3;
	cin>>m3;


	for(int i=0;i<m3;i++){
		int x,y;
		cin>>x>>y;
		notLegal[2][x].push_back(y);
	}

	

		int start=2;
		int oo=1e9;

		multiset<int> exist;
			
			exist.insert(oo);
			for(int j=0;j<limit[start+1];j++){
				exist.insert(cost[start+1][j]);
			} 

		for(int i=0;i<limit[start];i++){
			for(int x:notLegal[2][i+1])
				exist.erase(exist.find(cost[start+1][x-1]));

			cost[start][i]+=*exist.begin();

			for(int x:notLegal[2][i+1])
				exist.insert(cost[start+1][x-1]);
		}
//end for desert and drink
		exist.clear();
		 start=1;
		 exist.insert(oo);
			for(int j=0;j<limit[start+1];j++){
				exist.insert(cost[start+1][j]);
			} 

		for(int i=0;i<limit[start];i++){

			for(int x:notLegal[1][i+1])
				exist.erase(exist.find(cost[start+1][x-1]));

			cost[start][i]+=*exist.begin();

			for(int x:notLegal[1][i+1])
				exist.insert(cost[start+1][x-1]);
		}

		exist.clear();
		 start=0;
		 exist.insert(oo);
			for(int j=0;j<limit[start+1];j++){
				exist.insert(cost[start+1][j]);
			} 
		int finalAns = INT_MAX;
		for(int i=0;i<limit[start];i++){
			for(int x:notLegal[0][i+1])
				exist.erase(exist.find(cost[start+1][x-1]));

			cost[start][i]+=*exist.begin();
			finalAns = min(finalAns,cost[start][i]);

			for(int x:notLegal[0][i+1])
				exist.insert(cost[start+1][x-1]);
		}
	//end for second drink
	if(finalAns<oo)
		cout<<finalAns<<endl;
	else
		cout<<"-1\n";
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