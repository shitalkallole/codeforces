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
vector<int> rev={0,1,5,0,0,2,0,0,8,0};
vector<vector<bool>> data(100,vector<bool>(100,0));
void compose(){
	vector<bool> valid={1,1,1,0,0,1,0,0,1,0};
	for(int i=0;i<=99;i++){
		for(int j=0;j<=99;j++){

			int r1 = i%10;
			int r2 = (i/10)%10;

			int r3 = j%10;
			int r4 = (j/10)%10;

			if(valid[r1] && valid[r2] && valid[r3] && valid[r4])
				data[i][j]=1;
		}
	}
}
void solve(){
	int h,m;
	cin>>h>>m;

	string data1;
	cin>>data1;

	int cH = (data1[0]-'0')*10+(data1[1]-'0');
	int cM = (data1[3]-'0')*10+(data1[4]-'0');


	bool check=false;
	for(int i=cH;i<h;i++){
		for(int j=0;j<m;j++){
			if(j==cM){
				check=true;
			}
			if(check && data[i][j]){
				//h
				int r2 = i%10;
				int r1 = (i/10)%10;

				//m
				int r4 = j%10;
				int r3 = (j/10)%10;

				int rH = rev[r4]*10 + rev[r3];
				int rM = rev[r2]*10 + rev[r1];

				if(rH>=0 && rH<h && rM>=0 && rM<m){
					cout<<r1<<r2<<":"<<r3<<r4<<endl;
					return;
				}
			}
		}
	}
	for(int i=0;i<=cH;i++){
		for(int j=0;j<m;j++){
			if(data[i][j]){
				//h
				int r2 = i%10;
				int r1 = (i/10)%10;

				//m
				int r4 = j%10;
				int r3 = (j/10)%10;

				int rH = rev[r4]*10 + rev[r3];
				int rM = rev[r2]*10 + rev[r1];

				if(rH>=0 && rH<h && rM>=0 && rM<m){
					cout<<r1<<r2<<":"<<r3<<r4<<endl;
					return;
				}
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
    cin>>t;
    compose();
    while(t--){
		solve();
    }
    return 0;
}