#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m) for(int i = 0; i < m; i ++)

vector<int> color;

bool dfs(vector<vector<int>>& graph, int node){
  FOR(j,graph[node].size()){
    int next_node = graph[node][j];
    if (color[next_node] == 3){
      color[next_node] = 3-color[node];
      if (!dfs(graph, next_node)){
        return false;
      }
    }
    else{
      if(color[next_node] == color[node]){
        return false;
      }
    }
  }
  return true;
}

int main(){
  int nodes, edges;
  cin >> nodes >> edges;
  vector<vector<int>> graph;
  graph = vector<vector<int>>(nodes);

  FOR(i,edges){
    int a,b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  color = vector<int>(nodes, 3);

  bool possible = true;

  FOR(i, nodes){
    if (color[i] == 3 && possible){
      color[i] = 1;
      if (!dfs(graph, i)){
        possible = false;
      }
    }
  }

  if (possible){
    cout << "YES\n";
  } else{
    cout <<"NO\n";
  }
}
