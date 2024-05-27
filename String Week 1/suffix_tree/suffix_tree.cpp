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
string text;

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


struct tree{
	tree* child[5];
	pii edge[5];
	tree(){
		for(int i=0; i<5; i++){
			child[i] = NULL;
		}
	}
}root;

void AddToTree(tree* node, int pos){
	if(pos == text.size())
		return ;
	int c = chartonum(text[pos]) ;
	// age ke bache nadasht
	if(node->child[c] == NULL){
		node->child[c] = new tree();
		node->edge[c] = make_pair(pos,(int)text.size()-pos);
		return;
	}
	// age bache dare
	int commonLen=0;
	for(int i=pos; i< text.size(); i++){
		if(commonLen == node->edge[c].S){
			// age bache dare vali yal bache prefix az reshte hast
			return AddToTree(node->child[c], pos+ commonLen);
		}
		if(text[i] == text[node->edge[c].F+commonLen]){
			commonLen++;
		}
		else{
			break;
		}
	}
	// age yal va reshte ekhtelaf dashtan
	int firstdiffindex= node->edge[c].F + commonLen;
	int firstdiff = chartonum(text[firstdiffindex]);
	int diffLen= node->edge[c].S - commonLen;
	tree* newnode = new tree();
	newnode->edge[firstdiff] = make_pair(firstdiffindex, diffLen);
	newnode->child[firstdiff] = node->child[c];
	node->child[c] = newnode;
	node->edge[c] = make_pair(pos,commonLen);
	return AddToTree(newnode, pos+commonLen);
}

void DFS(tree* node){
	for(int i=0;i <5; i++){
		if(node->child[i]){
			cout << text.substr(node->edge[i].F, node->edge[i].S) << '\n';
			
			DFS(node->child[i]);
		}
	}
}

int32_t main(){
	FASTIO;
	cin >> text;
	for(int i=0; i< text.size(); i++){
		AddToTree(&root, i);
	}
	DFS(&root);
    return 0;
}
