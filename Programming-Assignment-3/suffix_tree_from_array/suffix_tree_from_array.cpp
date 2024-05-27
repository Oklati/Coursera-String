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
const int MAXN = 1e6 + 10;
string t;
int order[MAXN], lcp[MAXN];

class Node{
public:
	Node* par;
	map<char,Node*> children;
	int dep, start, end;
	Node(){
		par = NULL;
		dep = 0;
		end = -1;
		start = -1;
	}
	Node(Node* par,int dep, int start, int end){
		this->par= par;
		this->dep = dep;
		this->start = start;
		this->end = end;
	}
};

Node* CreateNewLeaf(Node* node, int suffix){
	Node* leaf = new Node(node, t.size() - suffix, suffix + node->dep, t.size() - 1);
	node->children[t[leaf->start]] = leaf;
	return leaf;
}

Node* BreakingEdge(Node* node, int start, int offset){
	char firstChar = t[start];
	char midChar = t[start+offset];
	Node* midNode = new Node(node, node->dep + offset, start, start + offset - 1);
	midNode->children[midChar] = node->children[firstChar];
	node->children[firstChar]->par = midNode;
	node->children[firstChar]->start += offset;
	node->children[firstChar] = midNode;
	return midNode;
}

Node* STFromSA(){
	Node* root = new Node();
	int lcpPrev = 0;
	Node* curNode = root;
	for(int i=0; i< t.size(); i++){
		int suf = order[i];
		while( curNode->dep > lcpPrev){
			curNode = curNode->par;
		}
		if( curNode->dep == lcpPrev){
			curNode = CreateNewLeaf(curNode,suf);
		}
		else{
			int edgestart = order[i-1] + curNode->dep;
			int offset = lcpPrev - curNode->dep;
			Node* midNode = BreakingEdge(curNode,edgestart,offset);
			curNode = CreateNewLeaf(midNode,suf);
		}
		if(i+1 < t.size()){
			lcpPrev = lcp[i];
		}
	}
	return root;
}

void OutputEdges(Node* node) {
	if(node->start != -1){
		cout << node->start << ' ' << node->end+1 << '\n';
	}
	for(auto &e : node->children){
		OutputEdges(e.S);
	}
}

int32_t main(){
	FASTIO;
	cin >> t;
	for(int i=0; i< t.size(); i++)
		cin >> order[i];
	for(int i=0; i+1< t.size(); i++)
		cin >> lcp[i];
	Node* root = STFromSA();
	cout << t << '\n';
	OutputEdges(root);
    return 0;
}
