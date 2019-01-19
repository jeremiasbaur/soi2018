#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m) for(int i = 0; i < m ; i++)
#define ll long long

bool pair_comparison (pair<int,pair<int,int>>& a, pair<int,pair<int,int>> & b){
	return a.first<b.first;
}

int find(vector<int> & parent, int a) {
	if (a == parent[a]){
		return a;
	}
	return parent[a] = find(parent, parent[a]);
}

void unite(vector<int> & parent, int a, int b) {
	a = find(parent, a);
	b = find(parent, b);

	if (rand()%2){
		parent[a] = b;
	} else{
		parent[b] = a;
	}
}

void mst(vector<int> & parent, ll & cost_of_bones,vector<pair<int,pair<int,int>>> & edge_weight){
	FOR(i, edge_weight.size()){
		int cost = edge_weight[i].first;
		int a = edge_weight[i].second.first;
		int b = edge_weight[i].second.second;

		if (find(parent, a) != find(parent, b)){
			cost_of_bones -= cost;
			unite(parent, a, b);
		}
	}
}

signed main(){
	int nodes, edges;
	cin >> nodes >> edges;

	vector<vector<pair<int,int>>> graph = vector<vector<pair<int,int>>>(nodes);
	vector<pair<int,pair<int,int>>> edge_weight;
	vector<int> parent;

	FOR(i, nodes){
		parent.push_back(i);
	}

	ll cost_of_bones = 0;

	FOR(i, edges){
		int a, b, cost;
		cin >> a >> b >> cost;
		graph[a-1].push_back(make_pair(b-1, cost));
		graph[b-1].push_back(make_pair(a-1, cost));
		edge_weight.push_back(make_pair(cost, make_pair(a-1, b-1)));
		cost_of_bones += cost;
	}
	sort(edge_weight.begin(),edge_weight.end(), pair_comparison);
	mst(parent, cost_of_bones, edge_weight);
	cout << cost_of_bones;
}
