#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) //cerr << x << "\n"

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int zutaten, space, a;
  cin >> zutaten >> space;

  vector<int> rezept = vector<int>(zutaten,0);
  vector<int> lager = vector<int>(zutaten,0);

  FOR(i, zutaten){
    cin >> a;
    rezept[i] = a;
  }
  FOR(i, zutaten){
    cin >> a;
    lager[i] = a;
  }

  int mid, right, left, space_left, last;
  right = 2000000001;
  left = 0;

  while(right>left){
    space_left = space;
    mid = (left + right)/2;

    DEB("rezept:");
    FOR(i, zutaten){
      int needed_space = rezept[i]*mid-lager[i];
      DEB(needed_space);

      if (needed_space>0){
        space_left -= needed_space;
      }
      if(space_left<0){
        break;
      }
    }

    if (space_left < 0){
      right = mid;
    } else{
      left = mid+1;
      last = mid;
    }
    //mid = (left + right)/2;
    DEB("mid: ");
    //cout << left << " "<< mid << " "<<right << "\n";
  }
  //cout << left << " "<< mid << " "<<right << "\n";
  DEB((right+left)/2);
  DEB(last);
  cout << last;
}
