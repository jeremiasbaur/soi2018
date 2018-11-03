#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m) for(int i = 0; i < m; i ++)

struct street{
  int x, y, widht, height, nodeid;

  bool operator<(const street& a) const{
    if (x == a.x){
      return y < a.y;
    }
    else {
      return x < a.x;
    }
  }
};

struct comp{
  bool operator()(const int& a, const int& b) const {
    return a < b;
  }
};

int main(){
  int cases, x, y, widht, height, count_streets;
  cin >> cases;

  FOR(i, cases){
    cin >> widht >> height >> x >> y >> count_streets; // widht and height are mape size and x and y are stoffles coordinates
    vector<street> streets;
    vector<street> sorted_streets;

    FOR(j, count_streets){
      street current_street;
      cin >> current_street.x >> current_street.y >> current_street.widht >> current_street.height;
      current_street.nodeid = j;
      streets.push_back(current_street);
      sorted_streets.push_back(current_street);
    }

    sort(sorted_streets.begin(), sorted_streets.end());

    map<int, int, comp> m;
    FOR(j, count_streets){
      cout << sorted_streets[j].x << sorted_streets[j].y << sorted_streets[j].widht << sorted_streets[j].height << "\n";
      m.insert(make_pair(sorted_streets[j].nodeid, sorted_streets[j].x+sorted_streets[j].widht));
    }

    FOR(j, count_streets){
      cout << m[j];
    }

  }
}
