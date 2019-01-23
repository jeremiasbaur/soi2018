#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

signed main(){
  in length, lights_amount;
  cin >> length >> lights_amount;

  vector<pair<in,in>> lights = vector<pair<in,in>>(lights_amount);
  vector<in> dp = vector<in>(length+1,-1);
  dp[0] = 0;
  FOR(i, lights_amount){
    in light_length, cost;
    cin >> light_length >> cost;
    lights[i] = make_pair(light_length, cost);
    if (light_length>length){
      light_length = length;
    }
    dp[light_length]==-1 ? dp[light_length] = cost : dp[light_length] = min(cost,dp[light_length]); // condition ? true : false
  }

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
