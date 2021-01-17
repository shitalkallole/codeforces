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

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    // freopen("inputf.txt","r",stdin);
    // freopen("outputf.txt","w",stdout);
    
    int t=1;
    cin>>t;
    while(t--){
		int n,m;
		cin>>n>>m;

		string data;
		cin>>data;

		vector<int> preMax(n+1);
		vector<int> preMin(n+1);
		vector<int> preCur(n+1);    


		vector<int> postMax(n+1);
		vector<int> postMin(n+1);
		vector<int> postCur(n+1);

		int curMax=0,curMin=0,cur=0;
		for(int i=0;i<n;i++){
			if(data[i]=='+'){
				cur+=1;
				curMax=max(curMax,cur);
				curMin=min(curMin,cur);
			}
			else{
				cur-=1;
				curMax=max(curMax,cur);
				curMin=min(curMin,cur);
			}
			preMax[i+1]=curMax;
			preMin[i+1]=curMin;
			preCur[i+1]=cur;
		}	
		curMax=0,curMin=0,cur=0;
		for(int i=n-1;i>=0;i--){
			if(data[i]=='+'){
				cur+=1;
				curMax=max(curMax,cur);
				curMin=min(curMin,cur);
			}
			else{
				cur-=1;
				curMax=max(curMax,cur);
				curMin=min(curMin,cur);
			}
			postMax[i+1]=curMax;
			postMin[i+1]=curMin;
			postCur[i+1]=cur;
		}

		int l,r;
		for(int i=0;i<m;i++){
			cin>>l>>r;

			if(l==1 && r==n){
				cout<<"1\n";
			}
			else if(l==1){
				int min1 = -postMax[r+1];
				int max1 = -postMin[r+1];

				int ans = max1-min1+1;
				cout<<ans<<endl;
				//exlude first one
			}
			else if(r==n){
				int min1 = preMin[l-1];
				int max1 = preMax[l-1];

				int ans = max1-min1+1;
				cout<<ans<<endl;
				//exclude last one
			}
			else{
				int min1 = preMin[l-1];
				int max1 = preMax[l-1];

				int min2 = -postMax[r+1];
				int max2 = -postMin[r+1];
				
				min2 = preCur[n]-(0-min2);
				max2 = preCur[n]+(max2-0);

				int dif = preCur[r]-preCur[l-1];

				min2 = min2 - dif;
				max2 = max2 - dif;

				int ans=0;
				if(min1>max2 || max1<min2){
					ans=(max1-min1+1)+(max2-min2+1);
				}else{
					ans=max(max1,max2)-min(min1,min2)+1;
				}
				cout<<ans<<endl;
			}
		}
    }
    return 0;
}














