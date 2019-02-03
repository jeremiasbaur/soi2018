#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

signed main(){
  in width, height, queries;
  cin >> width >> height >> queries;

  vector<vector<in>> rectangle = vector<vector<in>>();

  FOR(i, height){
    rectangle.push_back(vector<in>());
    FOR(j, width){
      in value;
      cin >> value;
      rectangle[i].push_back(value);
    }
  }

  vector<vector<in>> ps_rec = vector<vector<in>> (height+1, vector<in>(width+1,0));

  for(in i = 1; i < height+1 ; i++){
    for(in j = 1; j < width+1 ; j++){
      ps_rec[i][j] = ps_rec[i-1][j] + ps_rec[i][j-1] - ps_rec[i-1][j-1] + rectangle[i-1][j-1];
    }
  }

  FOR(i, queries){
    in rsx, rsy, rex, rey;
    cin >> rsx >> rsy >> rex >> rey;
    rex++;
    rey++;
    cout << ps_rec[rey][rex] - ps_rec[rsy][rex] - ps_rec[rey][rsx] + ps_rec[rsy][rsx] << "\n";
  }
}
