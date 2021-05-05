
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
int N = 2e7+10;
vector<int> primeFactors(N,0);

void calPrimeFactors(){
	for(ll i = 2;i<N;i++){
		if(primeFactors[i]==0){
			for(ll j=i;j<N;j+=i){
				primeFactors[j]+=1;
			}	
		}
	}
}
int uniqueChar(const string &data){
	int n = data.length();
	vector<int> val(26);

	for(int i=0;i<n;i++)
		val[data[i]-'a']=1;

	int sum = 0;
	for(int i=0;i<26;i++)
		sum+=val[i];

	return sum;
}

int sum(ll num){
	int total=0;
	while(num){
		total+=num%10;
		num/=10;
	}
	return total;
}
void solve(){
	string source,target;
	int len;

	cin>>len;
	cin>>source>>target;

	vector<bool> s(len,false);
	vector<bool> t(len,false);

	bool bothSame=true;
	int last=-1;
	//process source
	int zero=0;
	int one=0;
	for(int i=0;i<len;i++){
		if(source[i]=='0')
			zero+=1;
		else
			one+=1;
		if(zero==one){
			s[i]=1;
			last=i;
		}

		if(source[i]!=target[i])
			bothSame=false;
	}


	//process target
	zero=0;
	one=0;
	for(int i=0;i<len;i++){
		if(target[i]=='0')
			zero+=1;
		else
			one+=1;
		if(zero==one)
			t[i]=1;
	}
	if(bothSame){
		cout<<"YES\n";
		return;
	}

	bothSame=true;
	for(int i=last+1;i<len;i++){
		if(source[i]!=target[i]){
			bothSame=false;
			break;
		}
	}
	if(!bothSame)
	{
		cout<<"NO\n";
		return;
	}

	for(int i=0;i<=last;i++){
		if(s[i]!=t[i]){
			cout<<"NO\n";
			return;
		}
	}

	int i=0;
	while(i<=last){
		vector<int> sZero;
		vector<int> sOne;
		vector<int> tZero;
		vector<int> tOne;

		int k=i;
		while(true){
			if(source[k]=='0')
				sZero.push_back(k);
			else
				sOne.push_back(k);

			if(target[k]=='0')
				tZero.push_back(k);
			else
				tOne.push_back(k);

			if(s[k]){
				break;
			}

			k+=1;
		}

		//validate only
		bool cond = true;
		int limit = sZero.size();
		for(int l=0;l<limit;l++){
			if(sZero[l]!=tZero[l]){
				cond=false;
			}
		}

		if(cond){
			bool cond1=true;
			for(int l=0;l<limit;l++){
				if(sOne[l]!=tOne[l]){
					cond1=false;
					break;
				}
			}
			if(!cond1){
				cout<<"NO\n";
				return;
			}
		}else{
			bool cond1=true;
			for(int l=0;l<limit;l++){
				if(sZero[l]!=tOne[l]){
					cond1=false;
				}
			}
			if(cond1){
				bool cond2=true;
				for(int l=0;l<limit;l++){
					if(sOne[l]!=tZero[l]){
						cond2=false;
						break;
					}
				}
				if(!cond2){
					cout<<"NO\n";
					return;
				}

			}else{
				cout<<"NO\n";
				return;
			}


		}


		i=k+1;
	}
	cout<<"YES\n";
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