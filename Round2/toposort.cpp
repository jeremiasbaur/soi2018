#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m) for(int i = 0; i < m ; i++)

bool dfs(const vector<vector<int>> & graph, vector<bool> & visited, vector<bool> & current_visited, vector<int> & toposort , int & node){
	visited[node] = true;
	current_visited[node] = true;

	FOR(i, graph[node].size()){
		int new_node = graph[node][i];
		if (current_visited[new_node]){
			return true;
		}
		if (visited[new_node]){
			continue;
		}
		if (dfs(graph, visited, current_visited, toposort, new_node)){
			return true;
		}
	}
	current_visited[node] = false;
	toposort.push_back(node);
	return false;
}

int main(){
	int nodes, edges;
	cin >> nodes >> edges;

	vector<vector<int>> graph = vector<vector<int>>(nodes);
	vector<bool> visited = vector<bool>(nodes, false);
	vector<bool> current_visited = vector<bool>(nodes, false);
	vector<int> toposort = vector<int>();

	FOR(i, edges){
		int a, b;
		cin >> a >> b;
		graph[b].push_back(a);
	}

	// toposort:

	FOR(i, nodes){
		if (visited[i]){
			continue;
		}
		if(dfs(graph, visited, current_visited, toposort, i)){
			toposort = vector<int>();
			break;
		}
	}

	if (toposort.size()!=0){
		cout << "POSSIBLE\n";
		FOR(i, toposort.size()){
			cout << toposort[i] << " ";
		}
	}
	else{
		cout << "IMPOSSIBLE";
	}

}
