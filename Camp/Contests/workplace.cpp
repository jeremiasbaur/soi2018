#include <bits/stdc++.h>
using namespace std;

#define DEB(x) //cerr << x << "\n"
#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)

int return_max(vector<int> get_max){
  int max_int = 0;
  FOR(i, get_max.size()){
    if (get_max[i]>max_int){
      max_int = get_max[i];
    }
  }
  return max_int;
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int tables, a;
  cin >> tables;

  vector<int> speed = vector<int>(tables,0);
  FOR(i, tables){
    cin >> a;
    speed[i] = a;
  }

  vector<vector<int>> dp = vector<vector<int>>(tables, vector<int>(4,0));
  dp[0][0] = 0; // 0
  dp[0][1] = 3*speed[0]; // 2
  dp[0][2] = 3*speed[0]; // 3
  dp[0][3] = 4*speed[0]; // 4

  for(int i = 1; i<tables; i++){
    dp[i][0] = return_max(dp[i-1]);
    if (i==tables-1){
      dp[i][1] = dp[i-1][1]+speed[i]*3;
    } else{
      dp[i][1] = dp[i-1][1]+speed[i]*2;
    }
    dp[i][2] = dp[i-1][1]+speed[i]*3;
    if (i-2<0){
      dp[i][3] = speed[i]*4;
    } else{
      dp[i][3] = dp[i-2][3] + speed[i]*4;
    }
    FOR(j,4){
      cout << dp[i][j] << " ";
    }
    cout << "\n";
  }
  cout << return_max(dp[tables-1]);
}
