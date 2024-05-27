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
const int MAXN = 2e6 + 10;
const int MOD = 1e9 + 7;
int pi[MAXN];

int32_t main(){
	FASTIO;
	string P,T;
	cin >> P >> T;
	int psize = P.size();
	P += "$" + T;
	int border=0;
	for(int i=1; i< P.size(); i++){
		while(border > 0 && P[i] != P[border]){
			border = pi[border-1];
		}
		if( P[i] == P[border]){
			border++;
		}
		pi[i] = border;
		if(i > psize && pi[i] == psize){
			cout << i - 2*psize << ' ';
		}
	}
    return 0;
}
