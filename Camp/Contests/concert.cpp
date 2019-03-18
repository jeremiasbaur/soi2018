#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) cerr << x << "\n"

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int people, a, pA, pB, blocked, amount;

  cin >> people;
  vector<int> p = vector<int>(people,0);

  FOR(i, people){
    cin >> a;
    p[i] = a;
  }

  amount = 0;
  FOR(i, people){
    pA = p[i];
    blocked = 0;
    for(int j = i+1; j<people; j++){

      if (j-1==i){
        amount++;
        blocked = p[j];
        continue;
      } else if (blocked<p[j] && pA>blocked){
        DEB("went here:");
        DEB(pA);
        DEB(p[j]);
        amount++;
        blocked = p[j];
        continue;
      }
    }
  }
  cout << amount;

}
