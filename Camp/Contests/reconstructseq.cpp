#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) //cerr << x << "\n"

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int a_zahlen, max_zahl, type;
  char zeichen;
  cin >> a_zahlen >> max_zahl >> type;

  vector<char> symbols = vector<char>(a_zahlen);
  vector<int> zahlen = vector<int>(a_zahlen);
  FOR(i, a_zahlen-1){
    cin >> zeichen;
    symbols[i] = zeichen;
  }

  int current_number = max_zahl/2;
  int max_number, min_number;
  max_number = 0;
  min_number = max_zahl;
  FOR(i, a_zahlen){
    max_number = max(max_number, current_number);
    min_number = min(min_number, current_number);
    if (i == a_zahlen-1){
      zahlen[i] = current_number;
    }
    if (symbols[i]=='<'){
      zahlen[i] = current_number;
      current_number++;
    }
    else if(symbols[i]=='>'){
      zahlen[i] = current_number;
      current_number--;
    } else{
      zahlen[i] = current_number;
    }
    max_number = max(max_number, current_number);
    min_number = min(min_number, current_number);
  }
  bool possible = true;
  if (max_number-min_number>=max_zahl){
    possible = false;
  }
  FOR(i, a_zahlen){
    if (possible){
      cout << zahlen[i]-min_number << " ";
    }
    else{
      cout << -1 << " ";
    }
  }
  DEB("");
  DEB(max_number);
  DEB(min_number);
}
