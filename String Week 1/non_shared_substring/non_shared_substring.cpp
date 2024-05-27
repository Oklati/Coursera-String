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
const int MAXN = 5e3 + 10;
string text= "";
string txt[4];
const int MAXCHAR= 6;
int minLen = 1e9;
pii segment = make_pair(-1,-1);
int height;

char numtochar(const int& n){
	switch(n){
		case 0:
			return '$';
		case 1:
			return '#';
		case 2:
			return 'A';
		case 3:
			return 'C';
		case 4:
			return 'G';
		case 5:
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
		case '#':
			return 1;
		case 'A':
			return 2;
		case 'C':
			return 3;
		case 'G':
			return 4;
		case 'T':
			return 5;
		default:
			cout << n << " NOT A CHARACTER" << endl;
			throw ;
	}
}


struct trie{
	trie* child[MAXCHAR];
	trie(){
		for(int i=0; i<6; i++){
			child[i] = NULL;
		}
	}
}root;

void AddToTrie(trie* node, const string& text, const int& pos){
	if(pos == text.size())
		return;
	int c = chartonum(text[pos]);
	if(node->child[c] == NULL){
		node->child[c] = new trie();
	}
	return AddToTrie(node->child[c],text,pos+1);
}

void TrieMatch(trie* node, const string& text, const int& pos){
	if(pos == text.size())
		return;
	int c = chartonum(text[pos]);
	if(node->child[c] == NULL){
		// update answer
		if(height < minLen){
			minLen = height+1;
			segment = make_pair(pos-height,height+1);
		}
	}
	else{
		height++;
		TrieMatch(node->child[c], text, pos+1);
		height--;
	}
}


int32_t main(){
	FASTIO;
	cin >> txt[1] >> txt[2] ;
	for(int i=0; i< txt[2].size(); i++){
		AddToTrie(&root, txt[2], i);
	}
	for(int i=0; i< txt[1].size(); i++){
		TrieMatch(&root, txt[1], i);
	}
	cout << txt[1].substr(segment.F, segment.S) << endl;
    return 0;
}
