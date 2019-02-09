#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  in width, height, queries;
  cin >> width >> height >> queries;

  vector<vector<in>> rectangle = vector<vector<in>>(height+1, vector<in>(width+1));

  in value;
  FOR(i, height){
    FOR(j, width){
      cin >> value;
      rectangle[i][j] = value;
    }
  }

  //vector<vector<in>> ps_rec = vector<vector<in>> (height+1, vector<in>(width+1,0));
  vector<vector<in>> ps_rec = vector<vector<in>>(height+1, vector<in>(width+1));

  for(in i = 1; i < height+1 ; i++){
    //ps_rec.push_back(vector<in>());
    //ps_rec[i].push_back(0);
    for(in j = 1; j < width+1 ; j++){
      ps_rec[i][j] = ps_rec[i-1][j] + ps_rec[i][j-1] - ps_rec[i-1][j-1] + rectangle[i-1][j-1];
      //ps_rec[i].push_back(ps_rec[i-1][j] + ps_rec[i][j-1] - ps_rec[i-1][j-1] + rectangle[i-1][j-1]);
    }
  }

  in rsx, rsy, rex, rey, ans;
  FOR(i, queries){
    cin >> rsx >> rsy >> rex >> rey;
    rex++;
    rey++;
    ans = ps_rec[rey][rex] - ps_rec[rsy][rex] - ps_rec[rey][rsx] + ps_rec[rsy][rsx];
    cout << ans << '\n';
  }
}
