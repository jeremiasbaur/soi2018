#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

void dijkstra(vector<vector<pair<in,in>>>& graph, vector<in>& distance){
  priority_queue<pair<in,in>> queue;
  queue.push(make_pair(0,0)); // first is distance to origin and second is node

  while (!queue.empty()) {
    in cost = -1*queue.top().first;
    in node = queue.top().second;
    queue.pop();

    if(distance[node] != -1 && distance[node] < cost){
      continue;
    }

    FOR(i, graph[node].size()){
      in new_node = graph[node][i].first;
      in cost_new_node = graph[node][i].second;
      if (distance[new_node] == -1 || cost_new_node+cost < distance[new_node]){
        //cout << node << " :: "<< new_node << " :: " << cost_new_node+distance[node] << "\n";
        distance[new_node] = cost_new_node+cost;
        queue.push(make_pair(distance[new_node]*-1, new_node));
      }
    }
  }
}

signed main(){
  in nodes, edges;
  cin >> nodes >> edges;

  vector<vector<pair<in,in>>> graph = vector<vector<pair<in,in>>>(nodes);
  vector<in> distance = vector<in>(nodes,-1);
  FOR(i, edges){
    in a, b, cost;
    cin >> a >> b >> cost;
    graph[a-1].push_back(make_pair(b-1,cost));
    graph[b-1].push_back(make_pair(a-1,cost));
  }
  distance[0] = 0;
  dijkstra(graph, distance);
  -1 != distance[nodes-1] ? cout << distance[nodes-1] : cout << "Impossible";
}
