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
	int n;
	cin>>n;

	int total = 2*n;
	vector<int> data(total);
	for(int i=0;i<total;i++)
		cin>>data[i];

	sort(data.rbegin(),data.rend());

	vector<int> possibility;
	for(int i=1;i<total;i++)
		possibility.push_back(data[i]+data[0]);

	bool finalAns=false;
	int globalX=0;
	vector<pair<int,int>> toShow;
	for(int i=0;i<total-1;i++){
		toShow.clear();
		int maximum = data[0];
		int nextG=0;
		
		map<int,int> exist;
		for(int j=0;j<total;j++){
			auto it = exist.find(data[j]);
			if(it==exist.end())
				exist.insert({data[j],1});
			else
				it->second+=1;
		}

		int limit = total;
		int add = possibility[i];
		globalX = add;
		bool tempAns=true;
		while(limit!=0){
			int rem = add-maximum;
			auto it = exist.find(rem);

			if(rem==maximum && it!=exist.end() && it->second<2){
				tempAns=false;
				break;
			}
			if(it!=exist.end() && it->second!=0){
				it->second-=1;

				auto it1 = exist.find(maximum);
				it1->second-=1;

				toShow.push_back({rem,maximum});
				//find next greater
				nextG+=1;
				bool inside=true;
				while(nextG<total){
					auto it2 = exist.find(data[nextG]);
					if(it2->second!=0){
						inside=false;
						add = maximum;
						maximum = data[nextG]; 
						break;
					}
					nextG+=1;
				}
				if(inside){
					break;
				}
			}else{
			//rem not present so answer is not possible
				tempAns=false;
				break;
			}
			limit-=2;
		}
		if(tempAns){
			finalAns=true;
			break;
		}
	}
	if(finalAns){
		cout<<"YES"<<endl;
		cout<<globalX<<endl;

		for(int i=0;i<n;i++)
			cout<<toShow[i].first<<" "<<toShow[i].second<<endl;
	}
	else
		cout<<"NO"<<endl;
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



