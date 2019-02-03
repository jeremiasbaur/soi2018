#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

in find(vector<pair<in,in>>& graph, in a){
  if (a == graph[a].second){
    return a;
  }
  return find(graph, graph[a].second);
}

void unite(vector<pair<in,in>>& graph, in a, in b, bool time){
  in a_p, b_p;
  a_p = find(graph, a);
  b_p = find(graph, b);
  if (time){
    a > b ? graph[a].second = b_p : graph[b].second = a_p;
  } else{
    graph[b].second = a_p;
  }
}

signed main(){
  bool time;
  in lands, queries;
  cin >> time >> lands >> queries;

  vector<pair<in,in>> graph = vector<pair<in,in>>(lands);
  FOR(i, lands){
    graph[i] = make_pair(i,i);
  }

  FOR(i, queries){
    in a, b;
    cin >> a;
    if (a==-1){
      FOR(j, lands){
        cout << graph[j].second+1 << " ";
      }
      cout << "\n";
    } else{
      cin >> b;
      unite(graph, a-1, b-1, time);
    }
  }
}
