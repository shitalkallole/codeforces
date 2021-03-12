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

int getUpper(vector<int> &position,int upper){
	int l = 0;
	int r = position.size()-1;

	int ans=-1;
	while(l<=r){
		int mid = (l+r)/2;
		if(position[mid]<=upper){
			ans=mid;
			l=mid+1;
		}
		else{
			r = mid-1;
		}
	}
	return ans;
}
int getLower(vector<int> &position,int lower){
	int l = 0;
	int r = position.size()-1;

	int ans=-1;
	while(l<=r){
		int mid = (l+r)/2;
		if(position[mid]>=lower){
			ans=mid;
			r = mid-1;
		}
		else{
			l = mid+1;
		}
	}
	return ans;
}
int cal(vector<int> &box,vector<int> &position){
	int n = box.size();
	int m = position.size();

	if(n==0 || m==0)
		return 0;

	vector<int> suffix(n+1);
	int i,j;
	i=n-1;
	j=m-1;


	//precalculating number of already on special position
	while(i>=0 && j>=0){
		if(box[i]>position[j]){
			suffix[i] = suffix[i+1];
			i--;
		}
		else if(box[i]<position[j]){
			j--;
		}
		else{
			suffix[i]=1+suffix[i+1];
			i--;
			j--;
		}
	}
	if(j<0){
		//some of the boxes remaining
		while(i>=0){
			suffix[i]=suffix[i+1];
			i--;
		}
	}

	int globalAns=suffix[0];

	bool first=false;
	int k1,l1;
	for(int i=0;i<n;i++){
		int lower = box[i]-i;
		int upper;
		if(i==n-1)
			upper = position[m-1];//assigning last upp - validity
		else
			upper = box[i+1]-1;


		int l = getLower(position,lower);
		if(l == -1)
			break;
		int u = getUpper(position,upper);
		if(u<l){
			globalAns = max(globalAns,suffix[i+1]);
		}else{
			if(first){
				int count = i+1;
				int currentMax=0;

				while(l1<=u){
					int dist = position[l1]-position[k1]+1;
					if(dist<=count){
						currentMax = max(currentMax,l1-k1+1);
						l1+=1;
					}else{
						k1+=1;
					}
				}
				globalAns = max(globalAns,suffix[i+1]+currentMax);

			}else{
				int k=l;
				int count = i+1;
				int currentMax = 0;
				while(l<=u){
					int dist = position[l]-position[k]+1;
					if(dist<=count){
						currentMax = max(currentMax,l-k+1);
						l+=1;
					}
					else{
						k+=1;
					}
				}//while end
				globalAns = max(globalAns,suffix[i+1]+currentMax);
				first=true;
				k1=k;
				l1=l;
			}
		}
	}
	return globalAns;
}
void solve(){
	int n,m;
	cin>>n>>m;

	vector<int> boxPos,boxNeg;
	vector<int> specialPos,specialNeg;

	int temp;
	for(int i=0;i<n;i++){
		cin>>temp;
		if(temp<0)
			boxNeg.push_back(-temp);
		else
			boxPos.push_back(temp);
	}


	for(int i=0;i<m;i++){
		cin>>temp;
		if(temp<0)
			specialNeg.push_back(-temp);
		else
			specialPos.push_back(temp);
	}
	reverse(boxNeg.begin(),boxNeg.end());
	reverse(specialNeg.begin(),specialNeg.end());

	cout<<cal(boxPos,specialPos)+cal(boxNeg,specialNeg)<<endl;
	
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