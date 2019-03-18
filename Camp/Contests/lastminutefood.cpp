#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) cerr << x << "\n"

struct gem{
  int left, time, gram;
};

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int time, sorten, t_pasta, g_pasta;
  cin >> time >> sorten >> t_pasta >> g_pasta;

  vector<gem> gems = vector<gem>();
  vector<vector<int>> stock_left = vector<vector<int>>();
  vector<int> stock = vector<int>(sorten+1,0);

  stock.push_back(5000);
  gem gemm;
  gemm.time = t_pasta;
  gemm.gram = g_pasta;
  gems.push_back(gemm);
  FOR(i, sorten){
    cin >> gemm.left >> gemm.time >> gemm.gram;
    gems.push_back(gemm);
    stock[i] = gemm.left;
  }

  stock_left.push_back(stock);

  vector<vector<pair<int,int>>> dp = vector<vector<pair<int,int>>>(time,vector<pair<int,int>>(sorten+1,make_pair(0,0)));
  FOR(i,sorten+1){
    dp[0][i] = make_pair(0,0);
  }
  FOR(y, sorten+1){
    FOR(x, time){
      cout << dp[x][y].first << " ";
    }
    DEB("");
  }
  for(int i = 1; i < time; i++){
    for(int j = 0; j < sorten+1; j++){
      if (j==0 && i-gems[j].time>=0){
        if (dp[i-gems[j].time][sorten].first + gems[j].gram > dp[i-1][sorten].first){
          dp[i][j].first = dp[i-gems[j].time][sorten].first + gems[j].gram;
          dp[i][j].second = dp[i-1][sorten].second;
          DEB("sdaf");
        } else{
          dp[i][j].first = dp[i-1][sorten].first;
          dp[i][j].second = dp[i-1][sorten].second;
        }
      }
      else if (i - gems[j].time >= 0){

      //else if (i - gems[j].time >= 0 && stock_left[ dp[i - gems[j].time][sorten].second ][j] > 0){
        if (dp[ i-gems[j].time ][sorten].first + gems[j].time > dp[i][j-1].first){
          dp[i][j].first = dp[ i-gems[j].time ][sorten].first + gems[j].time;
          stock = stock_left[ dp[i - gems[j].time][sorten].second ];
          stock[j]--;
          stock_left.push_back(stock);
          dp[i][j].second = stock_left.size()-1;
        }
      } else{
        dp[i][j] = dp[i][j-1];
      }
    }
    FOR(y, sorten+1){
      FOR(x, time){
        cout << dp[x][y].first << " ";
      }
      DEB("");
    }
  }
  cout << dp[time-1][sorten].first;
}
