#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define all(x) x.begin(),x.end()
#define FASTIO ios_base::sync_with_stdio(false), cin.tie(0)
#define txin ifstream cin("input.txt")
#define txout ofstream cout("output.txt")
using namespace std;
typedef long long ll ;
typedef long double ld;
typedef pair<int,int> pii ;
//mt19937 r(chrono::steady_clock::now().time_since_epoch().count()) ;
const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;
ll w[MAXN];
ll dp[MAXN];

int32_t main(){
	FASTIO;
	string s;
	cin >> s;
	string list[s.size()];
	list[0] = s;
	for(int i=1; i<s.size(); i++){
		list[i] = s;
		for(int j=0; j+2< s.size(); j++){
			list[i][j] = list[i-1][j+1];
		}
		list[i][s.size()-2] = list[i-1][s.size()-1];
		list[i][s.size()-1] = list[i-1][0];
		//~ cout << list[i] << endl;
	}
	sort(list,list+(int)s.size());
	for(int i=0; i< s.size(); i++){
		cout << list[i][s.size()-1] ;
	}
    return 0;
}
