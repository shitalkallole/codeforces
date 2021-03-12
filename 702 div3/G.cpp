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

int query(vector<pair<ll,int>> &data,ll x,int n,vector<int>&postfix){
	int start=0;int end=n-1;
	int ans=-1;
	bool got=false;
	while(start<=end){
		int m = (start+end)/2;
		if(data[m].first>=x){
			got=true;
			ans=postfix[m];
			end=m-1;
		}else{
			start=m+1;
		}
	}

	return ans;
}
void solve(){
	int n,m;
	cin>>n>>m;

	vector<pair<ll,int>> data(n);
	ll temp;

	for(int i=0;i<n;i++){
		cin>>temp;
		if(i==0){
			data[i].first=temp;
			data[i].second=i;
		}
		else{
			data[i].first=data[i-1].first+temp;
			data[i].second=i;
		}
	} 
	ll finalVal = data[n-1].first;
	sort(data.begin(),data.end());

	vector<int> postfix(n);
	postfix[n-1]=data[n-1].second;

	for(int i=n-2;i>=0;i--){
		postfix[i]=min(data[i].second,postfix[i+1]);
	}

	ll x;
	for(int i=0;i<m;i++){
		cin>>x;

		if(data[n-1].first>0){
			if(x<=data[n-1].first){
				cout<<query(data,x,n,postfix)<<" ";
			}
			else
			{
				if(finalVal>0){
					ll newX=x-data[n-1].first;

					ll div = newX/finalVal;
					ll rem = newX%finalVal;

					if(rem!=0){
						newX = x-(finalVal*(div+1));
						int p = query(data,newX,n,postfix);
						cout<<p+(n*(div+1))<<" ";
					}
					else{
						int p = query(data,data[n-1].first,n,postfix);
						cout<<p+(div*n)<<" ";
					}
				}
				else{
					cout<<"-1 ";
				}
			}
		}
		else{
			cout<<"-1 ";
		}
	}
	cout<<endl;

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



