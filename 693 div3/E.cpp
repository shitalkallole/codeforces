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
int binary(vector<pair<pair<ll,ll>,int>> &data,ll h,ll w,int n,vector<pair<ll,int>> &suff){

	int i=0,j=n-1;
	int ans;
	bool got=false;

	while(i<=j){
		int m = (i+j)/2;
		if(data[m].first.first<h){
			got=true;
			ans=m;
			j=m-1;
		}else{
			i=m+1;
		}
	}
	if(!got)
		return -2;

	if(suff[ans].first<w)
		return suff[ans].second;
	return -2;
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
    	int n;
    	cin>>n;

    	vector<pair<pair<ll,ll>,int>> height(n);
    	vector<pair<pair<ll,ll>,int>> width(n);
    	vector<pair<ll,ll>> data(n);
    	ll h,w;
    	for(int i=0;i<n;i++){
    		cin>>h>>w;
    		data[i].first=h;
    		data[i].second=w;

    		height[i].first.first=h;
    		height[i].first.second=w;
    		height[i].second=i;

    		width[i].first.first=w;
    		width[i].first.second=h;
    		width[i].second=i;
    	}

    	sort(height.begin(),height.end(),greater<>());
    	sort(width.begin(),width.end(),greater<>());

    	vector<pair<ll,int>> suffH(n);
    	vector<pair<ll,int>> suffW(n);

    	suffH[n-1].first=height[n-1].first.second;
    	suffH[n-1].second=height[n-1].second;

    	for(int i=n-2;i>=0;i--){
    		if(height[i].first.second<suffH[i+1].first){
    			suffH[i].first=height[i].first.second;
    			suffH[i].second=height[i].second;
    		}else{
    			suffH[i].first=suffH[i+1].first;
    			suffH[i].second=suffH[i+1].second;
    		}
    	}

    	suffW[n-1].first=width[n-1].first.second;
    	suffW[n-1].second=width[n-1].second;
		
		for(int i=n-2;i>=0;i--){
    		if(width[i].first.second<suffW[i+1].first){
    			suffW[i].first=width[i].first.second;
    			suffW[i].second=width[i].second;
    		}else{
    			suffW[i].first=suffW[i+1].first;
    			suffW[i].second=suffW[i+1].second;
    		}
    	}    	

    	for(int i=0;i<n;i++){
    		int index = binary(height,data[i].first,data[i].second,n,suffH);
    		if(index==-2){
    			index = binary(width,data[i].first,data[i].second,n,suffW);
    		}
    		cout<<index+1<<" ";
    	}
    	cout<<endl;
    	
    }
    return 0;
}














