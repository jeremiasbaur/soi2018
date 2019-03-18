#include <bits/stdc++.h>
using namespace std;

#define DEB(x) //cerr << x << "\n"
#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)

vector<bool> visited;
int started;

bool dfs(vector<vector<int>>& graph, int node, int parent, bool down){
  DEB(node);
  visited[node] = true;
  if (graph[node].size()!=2){
    return false;
  }
  FOR(i, graph[node].size()){
    int new_node = graph[node][i];

    if (down && started==new_node){
      visited[new_node] = true;
      return true;
    }

    if (parent == -1 && new_node > node){
      DEB("1--");
      if (dfs(graph, new_node, node, down)){
        return true;
      }
    } else if (parent==-1){
      DEB("2--");
      continue;
    } else if (new_node > node){
      DEB("3--");
      if (dfs(graph, new_node, node, down)){
        return true;
      }
    } else if (!down && new_node != parent){
      DEB("4--");
      if (dfs(graph, new_node, node, !down)){
        return true;
      }
    }
  }
  return false;
}

signed main(){
  int nodes, edges;
  cin >> nodes >> edges;

  vector<vector<int>> graph = vector<vector<int>>(nodes, vector<int>());
  int a, b;
  FOR(i, edges){
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int counter = 0;
  visited = vector<bool>(nodes,false);

  FOR(i, nodes){
    started = i;
    if (!visited[i]){
      if (dfs(graph, i, -1, false)){
        counter++;
      }
    }
  }
  cout << counter << "\n";
}
