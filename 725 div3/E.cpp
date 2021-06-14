/*coder : shital basavraj kallole*/
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


vector<vector<int>> fourDirection = {{-1,0},{0,1},{1,0},{0,-1}};
vector<vector<int>> eightDirection = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};

//const ll M=1e9+7;

//to handle when remainder is -neg we add + M
//but when rem is +pos that time also we add so use %M
//so it will work for both
ll mod(ll n,ll M){
	return (n%M + M)%M;	
}
ll modAdd(ll a, ll b,ll M){
	return mod(mod(a,M)+mod(b,M),M);
}
ll modMul(ll a, ll b,ll M){
	return mod(mod(a,M)*mod(b,M),M);
}
ll modMinus(ll a, ll b,ll M){
	return mod(mod(a,M)-mod(b,M),M);
}
ll modpow(ll x, ll n, ll M) 
{ 
	if (n == 0) 
		return 1%M;
	if (n == 1)
		return x%M; 
	ll u = modpow(x,n/2,M); 
	u = modMul(u,u,M); 
	if (n%2) 
		u = modMul(u,x,M); 
	return u; 
}
//to find out gcd
ll gcd(ll a,ll b){
	if(b==0)
		return a;
	return gcd(b,a%b);
}
//to find out gcd and coefficients : ax+by = g
ll extendedGcd(ll a,ll b,ll &x,ll &y){
	if(b==0){
		x=1;
		y=0;
		return a;
	}
	ll x1,y1;
	ll g = extendedGcd(b,a%b,x1,y1);
	x = y1;
	y = x1 - y1*(a/b);
	return g;
}

//mod inverse is present only for coprime numbers that is gcd(a,m)=1
ll modInverse(ll a, ll m){
	ll g,x,y;
	g = extendedGcd(a,m,x,y);

	if(g==1){
		return (x%m+m)%m;
	}
	return -1;
}

//Chinese Remainder Theorem
ll crt(vector<ll> &P, vector<ll> &R){
	int n = P.size();
	vector<ll> X(n);

	ll productOfAllP=1;

	for(int i=0;i<n;i++)
		productOfAllP*=P[i];

	//each iteration calulates X[i]
	for(int i=0;i<n;i++){
		X[i]=R[i];
		ll mulOfInverse = 1;
		ll mul=1;
		for(int j=0;j<i;j++){
			mulOfInverse = modMul(mulOfInverse,modInverse(P[j],P[i]),P[i]);
			X[i] = modMinus(X[i],modMul(X[j],mul,P[i]),P[i]);
			mul = modMul(mul,P[j],P[i]);
		}
		X[i] = modMul(X[i],mulOfInverse,P[i]);
	}

	//calculating final X value
	ll finalX = 0;
	ll mul = 1;

	for(int i=0;i<n;i++){
		finalX = modAdd(finalX,modMul(X[i],mul,productOfAllP),productOfAllP);
		mul = modMul(mul,P[i],productOfAllP);
	}

	return finalX;
}
//check number is prime or not
bool isPrime(ll n){
	for(int i=2;i*i<=n;i++)
		if(n%i==0)
			return false;
	return true;
}

//disjoint set union
int getParent(vector<int>&parent,int s){
	if(parent[s]==s)
		return s;
	return getParent(parent,parent[s]);
}


//get prime numbers from 2 to 1e5
vector<int> primeNumbers;
void sieve(){
	int limit=1e5+1;
	vector<bool> prime(limit,true);
	for(ll i=2;i<limit;i++){
		if(prime[i]){
			primeNumbers.push_back(i);
			for(ll j=i*i;j<limit;j=j+i)
				prime[j]=false;
		}
	}
}
//new co-ordinate must be valid
bool insideGrid(int x,int y,int n,int m){
	if(x>=0 && x<n && y>=0 && y<m)
		return true;
	return false;
}
int isAssign(string &str, char ch){
	int len = str.length();

	for(int i=0;i<len;i++)
		if(str[i]==ch)
			return i;

	return -1;
}
ll haha(string &str){
	int len = str.length();
	int ans = 0 ;

	if(len<4)
		return ans;
	for(int i=0;i<=len-4;i++){
		string tmp = str.substr(i,4);
		if(tmp=="haha")
			ans+=1;
	}

	return ans;
}
void solve(){
	int n;
	cin>>n;

	cin>>ws;

	vector<string> data(n);
	map<string,ll> count;
	map<string,string> pre;
	map<string,string> suff;

	for(int i=0;i<n;i++)
		getline(cin,data[i]);

	ll ans = 0;
	for(int i=0;i<n;i++){
		int colon = isAssign(data[i],':');
		//cout<<colon<<endl;
		if(colon!=-1){
			string var = data[i].substr(0,colon-1);
			string finalStmt = data[i].substr(colon+3);
			//cout<<var<<sp<<finalStmt<<endl;
			int finalStmtSize = finalStmt.size(); 
			ll middle = haha(finalStmt);
			string insertPre = finalStmt.substr(0,min(3,finalStmtSize));
			string insertPost = finalStmt.substr(max(finalStmtSize-3,0),min(3,finalStmtSize));
			
			count[var] = middle;
			pre[var] = insertPre;
			suff[var] = insertPost;

			ans = middle;	

			//cout<<var<<sp<<finalStmt<<sp<<middle<<sp<<insertPre<<sp<<insertPost<<sp<<ans<<endl;
			//cout<<middle<<endl;
		}
		else{
			int equal = isAssign(data[i],'=');
			int plus = isAssign(data[i],'+');

			string var1 = data[i].substr(0,equal-1);
			string var2 = data[i].substr(equal+2,(plus-1)-(equal+2));
			string var3 = data[i].substr(plus+2);


			ll A1 = count[var2];
			ll A2 = count[var3];
			string compose = suff[var2]+pre[var3]; 
			ll A3 = haha(compose);

			ans = A1+A2+A3;

			count[var1] = ans;
			if(pre[var2].length()<=2){
				int l1 = pre[var3].length();
				int need = 3-(pre[var2].length());
				string newP = pre[var2]+(pre[var3].substr(0,min(l1,need))); 
				pre[var1] = newP;
			}
			else
				pre[var1] = pre[var2];

			if(suff[var3].length()<=2){
				int l1 = suff[var2].length();
				int need = 3 - (suff[var3].length());
				string newS = (suff[var2].substr(max(l1-need,0),min(l1,need)))+suff[var3];
				suff[var1] = newS;
			}
			else
				suff[var1] = suff[var3];
			//cout<<var1<<sp<<var2<<sp<<var3<<sp<<A1<<sp<<A2<<sp<<A3<<endl;
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
    cin>>t;
    while(t--){
		solve();
    }
    return 0;
}