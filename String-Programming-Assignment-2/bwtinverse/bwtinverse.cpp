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
typedef pair<int,char> pic ;
//mt19937 r(chrono::steady_clock::now().time_since_epoch().count()) ;
const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;
int ind[MAXN], cnt[MAXN];

int32_t main(){
	FASTIO;
	string bwt;
	cin >> bwt;
	string srt=bwt;
	sort(all(srt));
	string ans="";
	for(int i=0; i < srt.size(); i++){
		int first = lower_bound(all(srt), bwt[i]) - srt.begin();
		ind[i] = first + cnt[bwt[i]];
		cnt[bwt[i]]++;
	}
	int index=0;
	do{
		ans += srt[index];
		index = ind[index];
	}while(index != 0);
	reverse(all(ans));
	cout << ans << endl;
    return 0;
}
