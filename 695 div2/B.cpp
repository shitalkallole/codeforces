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
    cin>>t;
    while(t--){
    	int n;
    	cin>>n;

    	vector<int> data(n);
    	for(int i=0;i<n;i++)
    		cin>>data[i];

    	int ans=0;
    	if(n>2){
    		vector<bool> contri(n,false);

    		int total=0;
    		for(int i=1;i<n-1;i++){
    			if(data[i]>data[i-1] && data[i]>data[i+1]){
    				total+=1;
    				contri[i]=true;
    			}
    			else if(data[i]<data[i-1] && data[i]<data[i+1]){
    				total+=1;
    				contri[i]=true;
    			}
    		}

    		int best=total;
    		for(int i=0;i<n;i++){
    			if(i==0){
    				if(contri[i+1])
    					best=min(best,total-1);
    			}
    			else if(i==n-1){
    				if(contri[i-1])
    					best=min(best,total-1);
    			}
    			else{
    				//assigned left one
    				int cur = data[i-1];
    				int count=0;

    				//check for middle
    				if(contri[i])
    					count+=1;
    				//check for left
    				if(contri[i-1])
    					count+=1;

    				if(i+1!=(n-1)){
    					bool flag=false;
    					if(data[i+1]>cur && data[i+1]>data[i+2])
    						flag=true;
    					else if(data[i+1]<cur && data[i+1]<data[i+2])
    						flag=true;

    					if(contri[i+1]){
    						if(!flag)
    							count+=1;
    					}else{
    						if(flag)
    							count-=1;
    					}
    				}


    				//assigned right one
    				cur = data[i+1];
    				int count1=0;

    				//check for middle
    				if(contri[i])
    					count1+=1;
    				//check for right
    				if(contri[i+1])
    					count1+=1;

    				if(i-1!=0){
    					bool flag=false;
    					if(data[i-1]>cur && data[i-1]>data[i-2])
    						flag=true;
    					else if(data[i-1]<cur && data[i-1]<data[i-2])
    						flag=true;

    					if(contri[i-1]){
    						if(!flag)
    							count1+=1;
    					}else{
    						if(flag)
    							count1-=1;
    					}
    				}

    				best=min(best,total-max(count,count1));

    			}
    		}
    		ans=best;
    	}
    	cout<<ans<<endl;
    }
    return 0;
}














