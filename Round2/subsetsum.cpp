#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

bool subsetsum(vector<in>&usable_numbers, in sum){
  vector<vector<bool>> dp = vector<vector<bool>>(usable_numbers.size()+1, vector<bool>(sum+1,false));

  FOR(i,usable_numbers.size()+1){
    dp[i][0] = true;
  }

  for(in i = 1; i<usable_numbers.size()+1;++i){
    for(in j = 1; j < sum+1;++j){
      if (j<usable_numbers[i-1]){
        dp[i][j] = dp[i-1][j]; // check if sum can already be reached with other numbers
      }
      if (j>=usable_numbers[i-1]){
        dp[i][j] = dp[i-1][j] || dp[i-1][j-usable_numbers[i-1]]; // check if current sum - value of number is possible
      }
    }
  }
  return dp[usable_numbers.size()][sum];
}

signed main(){
  in numbers, sum;
  cin >> numbers >> sum;

  vector<in> usable_numbers = vector<in>();
  FOR(i,numbers){
    in number;
    cin >> number;
    usable_numbers.push_back(number);
  }

  subsetsum(usable_numbers, sum) ? cout << "YES" : cout << "NO";
}
