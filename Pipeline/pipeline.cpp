#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m) for(int i = 0; i < m; i ++)

int main(){
  ifstream cin("pipeline-sub2-attempt7.txt");
  ofstream cout("output.txt");
  int cases, pumps_count, max_pumps, ltc;
  cin >> cases;
  FOR(i, cases){
    cin >> pumps_count >> max_pumps;
    vector<int> pumps_station;
    vector<bool> pump_true;
    int ltc = 0;
    int last = 0;
    FOR(j, pumps_count){
      int pump;
      cin >> pump;
      pumps_station.push_back(pump);
      pump_true.push_back(false);
      if (j>0 && pump-last > ltc){
        ltc = pump-last;
      }
      last = pump;
    }
    int count_pumps = -1;
    while (count_pumps > max_pumps || count_pumps==-1){
      FOR(j, pumps_count){
        pump_true[j] = false;
      }
      int j = 1;
      int looking_from = 0;
      bool impossible = false;

      while (j != pumps_count){
        if (pumps_station[j]-pumps_station[j-1]>ltc){
          impossible = true;
          break;
        } else if (pumps_station[j]-pumps_station[looking_from] == ltc){
          pump_true[j] = true;
          pump_true[looking_from] = true;
          looking_from = j;
        } else if (pumps_station[j]-pumps_station[looking_from] > ltc){
          pump_true[j-1] = true;
          pump_true[looking_from] = true;
          looking_from = j-1;
        }
        j++;
      }

      if (impossible){
        ltc++;
        continue;
      }

      pump_true[0] = true;
      pump_true[pumps_count-1] = true;
      count_pumps = 0;
      FOR(j, pumps_count){
        if (pump_true[j]){
          count_pumps++;
        }
      }
      ltc++;
    }
    int j = 0;
    while (count_pumps!=max_pumps){
      if (!pump_true[j]){
        pump_true[j] = true;
        count_pumps++;
      }
      j++;
    }

    string output = to_string(pumps_station[0]) + " ";
    last = pumps_station[0];
    ltc = 0;
    for(int j = 1; j<pumps_count; j++){
      if (pump_true[j]){
        output += to_string(pumps_station[j]) + " ";
        ltc = max(ltc, pumps_station[j]-last);
        last = pumps_station[j];
      }
    }
    if (count_pumps > 9000){
      cout << "Case #" << i << ": " << ltc << "\n" << "Over 9000" <<"\n";
    } else{
      cout << "Case #" << i << ": " << ltc << "\n" << output <<"\n";
    }
  }
}
