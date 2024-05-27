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
const int SIGMA = 7;
int order[MAXN], clas[MAXN];
int neworder[MAXN], newclas[MAXN];
int cnt[MAXN][SIGMA], first[SIGMA];
string bwt="",srt="";

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

void SortCharacters(const string& t){
	int count[SIGMA]; fill(count,count+SIGMA,0);
	for(int i=0; i< t.size(); i++){
		count[chartonum(t[i])]++;
	}
	for(int i=1; i< SIGMA; i++){
		count[i] += count[i-1];
	}
	for(int i=t.size()-1; i >= 0; i--){
		int c = chartonum(t[i]);
		count[c]--;
		order[count[c]] = i;
	}
}
void ComputeClass(const string& t){
	for(int i=1; i< t.size(); i++){
		if(t[order[i]] != t[order[i-1]]) {
			clas[order[i]] = clas[order[i-1]] + 1;
		}
		else {
			clas[order[i]] = clas[order[i-1]];
		}
	}
}
void SortNext(const string& t, int L){
	int tsize = t.size() ;
	int count[tsize]; fill(count, count+tsize,0);
	for(int i=0; i< tsize; i++) {
		count[clas[i]] = count[clas[i]] + 1;
	}
	for(int i=1; i< tsize; i++) {
		count[i] += count[i-1];
	}
	for(int i=tsize-1; i>= 0; i--){
		int start = (order[i] - L + tsize) % tsize;
		int cl = clas[start];
		count[cl]--;
		neworder[count[cl]] = start;
	}
	for(int i=0; i< tsize; i++)
		order[i] = neworder[i];
}
void UpdateClass(int n, int len){
	for(int i=1; i< n; i++){
		int cur = order[i];
		int prev = order[i-1];
		int mid = cur + len;
		int midprev = (prev + len) % n;
		if(clas[cur] != clas[prev] || clas[mid] != clas[midprev]){
			newclas[cur] = newclas[prev] + 1;
		}
		else{
			newclas[cur] = newclas[prev];
		}
	}
	for(int i=0; i< n; i++)
		clas[i] = newclas[i];
}
void buildSufArray(const string& t){
	SortCharacters(t);
	ComputeClass(t);
	int len = 1;
	while (len < t.size()){
		SortNext(t,len);
		UpdateClass(t.size(),len);
		len *= 2;
	}
}

pii find(string &pat){
	int top=0, bot=srt.size()-1;
	while(top <= bot && bot < srt.size()){
		//~ cout << top << ' '<< bot << endl;
		if(pat.empty())
			return pii(top,bot);
		int c= chartonum(pat.back());
		pat.pop_back();
		top = first[c] + cnt[top][c];
		bot = first[c] + cnt[bot+1][c] -1;
	}
	//~ cout << top << ' '<< bot << endl;
	return pii(-1,-1);
}

int32_t main(){
	FASTIO;
	string t;
	cin >> t; t += '$';
	buildSufArray(t);
	for(int i=0; i< t.size(); i++){
		srt += t[order[i]];
		bwt += t[(order[i] - 1 + (int)t.size())%t.size()];
	}
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
	}
	int N; cin >> N;
	string pat;
	set<int> ans;
	while(N--){
		cin >> pat;
		pii A = find(pat);
		if(A.F != -1)
			for(int i=A.F; i<= A.S; i++){
				ans.insert(order[i]);
			}
	}
	for(auto x : ans){
		cout << x << ' ';
	}
    return 0;
}
