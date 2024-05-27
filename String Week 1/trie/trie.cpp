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

char numchar(int i){
	if(i == 0) return 'A';
	if(i == 1) return 'C';
	if(i == 2) return 'G';
	if(i == 3) return 'T';
}

int charnum(char a){
	if(a == 'A') return 0;
	if(a == 'C') return 1;
	if(a == 'G') return 2;
	if(a == 'T') return 3;
}

struct trie{
	static int num;
	trie* child[4];
	int index;
	bool leaf;
	trie(){
		for(int i=0; i< 4; i++){
			child[i] = NULL;
		}
		leaf = false;
	}
	trie(int index){
		this->index = index;
		trie();
	}
	void AddToTrie(string &s){
		if(s.empty()){
			this->leaf = true;
			return ;
		}
		int add = charnum(s.back());
		if(child[add] == NULL){
			child[add] = new trie();
			child[add]->index = ++num;
		}
		s.pop_back();
		child[add]->AddToTrie(s);
	}
	void traverse(){
		for(int i=0; i< 4; i++){
			if(child[i] != NULL){
				cout << this->index << "->" << child[i]->index << ':' << numchar(i) << '\n';
				child[i]->traverse();
			}
		}
	}
}root ;
int trie::num = 0;

bool match(trie* node, string& text, int index){
	if(node->leaf){
		return true;
	}
	int childaddress = charnum(text[index]);
	if(node->child[childaddress] == NULL || index == text.size()){
		return false;
	}
	return match(node->child[childaddress], text, index+1);
}

int32_t main(){
	FASTIO;
	int n;
	cin >> n;
	root.index = 0;
	for(int i=1; i<= n ;i++){
		string s;
		cin >> s;
		reverse(s.begin(), s.end()) ;
		root.AddToTrie(s) ;
	}
	root.traverse();
    return 0;
}
