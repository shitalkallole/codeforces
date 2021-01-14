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

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    // freopen("inputf.txt","r",stdin);
    // freopen("outputf.txt","w",stdout);
    
    int t=1;
    //cin>>t;
    while(t--){
    	int sum=0;
    	vector<int> total(3);
    	vector<ll> add(3);

    	for(int i=0;i<3;i++)
    	{
    		cin>>total[i];
    		sum+=total[i];
    	}

    	vector<int> mins;
    	for(int i=0;i<3;i++){
    		if(total[i]==1){
    			mins.push_back(i);
    		}
    	}


    	vector<pair<ll,int>> data(sum);
    	int prev=0;
    	ll totalSum=0;
    	for(int i=0;i<3;i++){
    		if(i!=0)
    			prev+=total[i-1];

    		for(int j=0;j<total[i];j++){
    			cin>>data[j+prev].first;
    			totalSum+=data[j+prev].first;
    			data[j+prev].second=i;
    			add[i]+=data[j+prev].first;
    		}
    	}

    	sort(data.begin(),data.end());

    	ll ans=0;
    	if(mins.size()!=0){
    		for(int i=0;i<mins.size();i++){
    			ans=max(ans,totalSum-(2*add[mins[i]]));
    		}
    	}
    	if(data[0].second!=data[1].second){

    		ans=max(ans,totalSum-2*(data[0].first+data[1].first));
    	}
    	else{
    		ll val1 = totalSum-(add[data[0].second]*2);
    		
    		int j=0;

    		while(data[j].second==data[0].second){
    			j+=1;
    		}
    		ll val2= totalSum-2*(data[0].first+data[j].first);

    		ans=max(ans,max(val1,val2));	
    	}
    	cout<<ans<<endl;

    }
    return 0;
}














