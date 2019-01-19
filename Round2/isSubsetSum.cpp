// random code in editor

#include <bits/stdc++.h>
using namespace std;
#define FOR(i, m) for(int i = 0; i < m; i ++)

bool isSubsetSum(vector<int> set, int n, int sum)
{
    bool subset[n+1][sum+1];
    //sum == 0 true
    for (int i = 0; i <= n; i++)
      subset[i][0] = true;

    //false if sum > 0
    for (int i = 1; i <= sum; i++)
      subset[0][i] = false;

     //botton up manner
     for (int i = 1; i <= n; i++)
     {
       for (int j = 1; j <= sum; j++)
       {
         if(j<set[i-1])
           subset[i][j] = subset[i-1][j];
         if (j >= set[i-1])
           subset[i][j] = subset[i-1][j] || subset[i - 1][j-set[i-1]];
       }
     }
     return subset[n][sum];
}
int main() {
  int N,X,value;
  cin >> N >> X;
  vector<int> set;
  FOR(i,N){
    cin >> value;
    set.push_back(value);
  }
  if (isSubsetSum(set, N, X) == true)
     cout << "YES";
  else
     cout << "NO";
}
