#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m) for(int i = 0; i < m; i ++)
#define DEB(x) //cerr << x << "\n"
#define int long long

vector<int> color;
vector<int> distances;

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

bool dfs2(vector<vector<int>>& graph, int node, int dist){
  FOR(j, graph[node].size()){
    int next_node = graph[node][j];
    if (distances[next_node] == -1){
      distances[next_node] = dist+1;
      if(dfs2(graph, next_node, dist+1)){
        return true;
      }
    }
    else {
      if(distances[node]-distances[next_node]%2!=0 && distances[node]!=1){
        return true;
      } else{
        return false;
      }
    }
  }
  return false;
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int nodes, edges;
  cin >> nodes >> edges;
  vector<vector<int>> graph;
  graph = vector<vector<int>>(nodes);

  FOR(i,edges){
    int a,b;
    cin >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  color = vector<int>(nodes, 3);

  bool possible = true;
  vector<int> more_vert = vector<int>();

  FOR(i, nodes){
    if (color[i] == 3 && possible){
      color[i] = 1;
      if (!dfs(graph, i)){
        possible = false;
      }
    }
    if (graph[i].size()>2){
      more_vert.push_back(i);
    }
  }

  if (!possible){
    cout << "YES\n";
  } else{
    cout <<"NO\n";
  }

  possible = false;
  int split_node = 0;
  FOR(i, more_vert.size()){
    if (possible){
      break;
    }
    split_node = more_vert[i];
    distances = vector<int>(nodes,-1);
    distances[split_node] = 0;
    FOR(j,graph[split_node].size()){
      if (dfs2(graph, graph[split_node][j], 0)){
        possible = true;
        break;
      }
    }
  }
  if (possible){
    cout << "YES\n";
  } else{
    cout <<"NO\n";
  }
}
