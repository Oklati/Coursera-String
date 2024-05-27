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
int cnt[MAXN][5], first[5];
string bwt,srt;

char numtochar(const int& n){
	switch(n){
		case 0:
			return '$';
		case 1:
			return 'A';
		case 2:
			return 'C';
		case 3:
			return 'G';
		case 4:
			return 'T';
		default:
			cout << n << " NOT A NUMBER" << endl;
			throw;
	}
}
int chartonum(const char& n){
	switch(n){
		case '$':
			return 0;
		case 'A':
			return 1;
		case 'C':
			return 2;
		case 'G':
			return 3;
		case 'T':
			return 4;
		default:
			cout << n << " NOT A CHARACTER" << endl;
			throw ;
	}
}

int find(string &pat){
	int top=0, bot=srt.size()-1;
	while(top <= bot && bot < srt.size()){
		//~ cout << top << ' '<< bot << endl;
		if(pat.empty())
			return bot-top+1;
		int c= chartonum(pat.back());
		pat.pop_back();
		top = first[c] + cnt[top][c];
		bot = first[c] + cnt[bot+1][c] -1;
	}
	//~ cout << top << ' '<< bot << endl;
	return 0;
}

int32_t main(){
	FASTIO;
	cin >> bwt;
	srt=bwt;
	sort(all(srt));
	for(int i=1; i<= bwt.size(); i++){
		for(int j=0; j< 5; j++){
			cnt[i][j] = cnt[i-1][j];
		}
		cnt[i][chartonum(bwt[i-1])]++;
	}
	for(int j=0; j< 5; j++){
		bool set=0;
		for(int i=0; i< srt.size(); i++){
			if(numtochar(j) == srt[i]){
				first[j] = i;
				set =1;
				break;
			}
		}
		if(!set){
			first[j] = srt.size();
		}
		//~ cout << first[j] << endl;
	}
	int p; cin >> p;
	string pat;
	while(p--){
		cin >> pat;
		cout << find(pat) << ' ';
	}
    return 0;
}
