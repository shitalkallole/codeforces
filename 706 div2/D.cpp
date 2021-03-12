//2*10^9   -- int
//9*10^18  -- long long int
//10^38    -- __int128_t 

//we also have long double
/*A better way to compare ﬂoating point numbers is to assume that 
two numbers are equal if the difference between them is less than ε, where ε is a small number.(ε=10^−9) */

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
//advanced binary search - aggresive cows
void solve(){
	int n;
	cin>>n;

	vector<int> data(n);
	for(int i=0;i<n;i++)
		cin>>data[i];

	vector<pair<int,int>> sol;
	
	int i=0;

	//for initial down
	while(i+1<n && data[i]>data[i+1]){
		i++;
	}
	if(i!=0){
		sol.push_back(make_pair(0,i+1));
	}
	while(i!=n-1){
		int count=0;
		//for up cal
		while(i+1<n && data[i+1]>data[i]){
			i+=1;
			count+=1;
		}
		count+=1;

		int count1=0;
		//for down cal
		while(i+1<n && data[i]>data[i+1]){
			i+=1;
			count1+=1;
		}
		if(count1!=0)//check end condition
			count1+=1;

		sol.push_back(make_pair(count,count1));
	}
	int limit = sol.size();
	vector<int> post(limit+1),pre(limit+1);

	for(int i=limit-1;i>=0;i--){
		post[i]=max(post[i+1],max(sol[i].first,sol[i].second));
	}

	for(int i=0;i<limit;i++){
		pre[i+1]=max(pre[i],max(sol[i].first,sol[i].second));
	}
	int ans=0;
	for(int i=0;i<sol.size();i++){
		//cout<<sol[i].first<<" "<<sol[i].second<<endl;
		if(sol[i].first!=0 && sol[i].second!=0){
			int maxima = max(sol[i].first,sol[i].second);
			if(maxima%2!=0){
				int myMax = max(post[i+1],pre[i]);
				if(maxima-1>=min(sol[i].first,sol[i].second))
				{
					//op
				}
				else if(myMax<maxima)
					ans+=1;
			}
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
    //cin>>t;
   
    while(t--){
		solve();
    }
    return 0;
}