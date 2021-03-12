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
	//advanced binary search - aggresive cows
	
	int n,k;
	cin>>n>>k;

	string data;
	cin>>data;

	if(n%k==0){

		vector<int> cnt(26);
		for(int i=0;i<n;i++){
			cnt[data[i]-'a']+=1;
		}

		bool ans=true;
		for(int i=0;i<26;i++){
			if(cnt[i]%k!=0){
				ans=false;
				break;
			}
		}
		

		if(!ans){
			for(int i=n-1;i>=0;i--){
				//sub current char count
				cnt[data[i]-'a']-=1;

				for(int j=data[i]-'a'+1;j<26;j++){
					cnt[j]+=1;

					int suffLength = n-i-1;
					int sum=0;

					vector<int> rem(26);
					for(int l=0;l<26;l++){
						rem[l]=(k-(cnt[l]%k))%k;
						sum+=rem[l];
					}
					if(sum<=suffLength){
						rem[0]+=(suffLength-sum);

						for(int m=0;m<i;m++)
							cout<<data[m];
						cout<<(char)(97+j);

						for(int p=0;p<26;p++)
						{
							for(int q=0;q<rem[p];q++)
								cout<<(char)(p+97);
						}
						cout<<endl;
						return;
					}
					cnt[j]-=1;
				}
			}
		}else{
			cout<<data<<endl;
		}
	}
	else{
		cout<<"-1\n";
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
   
    while(t--){
		solve();
    }
    return 0;
}