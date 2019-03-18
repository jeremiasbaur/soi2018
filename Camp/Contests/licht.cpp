#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) //cerr << x << "\n"

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int light_positions, lights_amount, height;
  cin >> light_positions >> lights_amount >> height;

  vector<pair<int,int>> light_pos = vector<pair<int,int>>(light_positions);
  vector<pair<int,int>> lights = vector<pair<int,int>>(lights_amount);

  int x, y;
  FOR(i, light_positions){
    cin >> x >> y;
    light_pos[i] = make_pair(x,y);
  }

  FOR(i, lights_amount){
    cin >> x >> y;
    lights[i] = make_pair(x, y);
    //dp[light_length]==-1 ? dp[light_length] = cost : dp[light_length] = min(cost,dp[light_length]); // condition ? true : false
  }

  vector<int> dp = vector<int>(length+1,-1);
  dp[0] = 0;

  for(int i = 1; i<=length;++i){
    if (dp[i]!=-1){
      FOR(j, lights_amount){
        in light_length, cost, next_pos;
        light_length = lights[j].first;
        cost = lights[j].second;
        i+light_length > length ? next_pos = length : next_pos = i+light_length;
        dp[next_pos]==-1 ? dp[next_pos] = dp[i] + cost : dp[next_pos] = min(cost+dp[i],dp[next_pos]);
      }
    }
  }
  cout << dp[length];
}
