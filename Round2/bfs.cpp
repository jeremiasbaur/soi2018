#include <bits/stdc++.h>
using namespace std;

#define FOR(i,m) for(int i = 0; i < m; i ++)

vector<vector<int>> graph;
vector<int> distances;

void bfs(){
	queue<int> bfs_queue;
	bfs_queue.push(0);
	while(!bfs_queue.empty()){
		int node = bfs_queue.front();
		bfs_queue.pop();
		for(int i = 0; i < graph[node].size(); i++){
			int new_node = graph[node][i];
			if(distances[node]+1<distances[new_node]){
				distances[new_node] = distances[node] + 1;
				bfs_queue.push(new_node);
			}
		}
	}
}

int main(){
	int nodes, edges;
	cin >> nodes >> edges;

	graph = vector<vector<int>>(nodes);
	distances = vector<int>(nodes,1000000);

	for(int i = 0; i<edges; i++){
		int a, b;
		cin >> a >> b;

		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	distances[0] = 0;
	bfs();
	cout << distances[nodes-1] << "\n";
}
