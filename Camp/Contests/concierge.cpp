#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) //cerr << x << "\n"

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int teilnehmer, time;
  cin >> teilnehmer;

  vector<int> arrival = vector<int>(teilnehmer);
  vector<int> difference = vector<int>(teilnehmer-1);
  vector<int> rooms = vector<int>(teilnehmer,-1);
  vector<int> t_room = vector<int>(teilnehmer,-1);

  FOR(i, teilnehmer){
    cin >> time;
    if (i>0){
      arrival[i] = time;
      difference[i-1] = arrival[i] - arrival[i-1];
      //DEB(difference[i]);
    }
    else{
      arrival[i] = time;
    }
  }
  bool possible = true;
  bool possible2 = true;
  int room;
  FOR(i, teilnehmer-1){
    room = (difference[i]/2);
    possible2 = false;
    DEB("teilnehmer: ");
    DEB(i+1);
    DEB(room);
    DEB("raumbelegung: ");
    DEB(difference[i]);
    DEB(difference[i]/2);
    if (room>teilnehmer){
      room = teilnehmer;
    }
    for(int j = room-1; j>=0; j--){
      //DEB(j);
      if (rooms[j] == -1){
        DEB("put here:");
        DEB(i+1);
        DEB(j);
        DEB("--");
        t_room[i] = j+1;
        rooms[j] = i+1;
        possible2 = true;
        break;
      }
    }
    /*FOR(i, teilnehmer){
      DEB(rooms[i]);
    }*/
    if (!possible2){
      possible = false;
      break;
    }
  }
  if (!possible){
    cout << "IMPOSSIBLE";
  } else{
    FOR(i, teilnehmer){
      if (rooms[i] == -1){
        t_room[teilnehmer-1] = i+1;
        //cout << teilnehmer << " ";
      }
      cout << t_room[i] << " ";
    }
  }

}
