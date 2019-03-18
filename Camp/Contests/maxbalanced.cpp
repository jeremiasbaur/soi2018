#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) cerr << x << "\n"

struct info{
  pair<int,int> a,b,c,d,e,f,g,h;
};

void zuweiser(char x, vector<info>& pos, vector<int>& last_pos, int i){
  if (i>0){
    pos[i] = pos[i-1];
  }
  if(x == 'a'){
    pos[i].a.first++;

    if (pos[i].a.second == -1){
      last_pos[i] = i;
      pos[i].a.second = i;
    } else{
      last_pos[i] = pos[i].a.second;
      pos[i].a.second = i;
    }
  }
  if(x == 'b'){
    pos[i].b.first++;

    if (pos[i].b.second == -1){
      last_pos[i] = i;
      pos[i].b.second = i;
    } else{
      last_pos[i] = pos[i].b.second;
      pos[i].b.second = i;
    }
  }
  if(x == 'c'){
    pos[i].c.first++;

    if (pos[i].c.second == -1){
      last_pos[i] = i;
      pos[i].c.second = i;
    } else{
      last_pos[i] = pos[i].c.second;
      pos[i].c.second = i;
    }
  }
  if(x == 'd'){
    pos[i].d.first++;

    if (pos[i].d.second == -1){
      last_pos[i] = i;
      pos[i].d.second = i;
    } else{
      last_pos[i] = pos[i].d.second;
      pos[i].d.second = i;
    }
  }
  if(x == 'e'){
    pos[i].e.first++;

    if (pos[i].e.second == -1){
      last_pos[i] = i;
      pos[i].e.second = i;
    } else{
      last_pos[i] = pos[i].e.second;
      pos[i].e.second = i;
    }
  }
  if(x == 'f'){
    pos[i].f.first++;

    if (pos[i].f.second == -1){
      last_pos[i] = i;
      pos[i].f.second = i;
    } else{
      last_pos[i] = pos[i].f.second;
      pos[i].f.second = i;
    }
  }
  if(x == 'g'){
    pos[i].g.first++;

    if (pos[i].g.second == -1){
      last_pos[i] = i;
      pos[i].g.second = i;
    } else{
      last_pos[i] = pos[i].g.second;
      pos[i].g.second = i;
    }
  }
  if(x == 'h'){
    pos[i].h.first++;

    if (pos[i].h.second == -1){
      last_pos[i] = i;
      pos[i].h.second = i;
    } else{
      last_pos[i] = pos[i].h.second;
      pos[i].h.second = i;
    }
  }
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  string eingabe;

  cin >> eingabe;

  info test;
  test.a = make_pair(0,-1);
  test.b = make_pair(0,-1);
  test.c = make_pair(0,-1);
  test.d = make_pair(0,-1);
  test.e = make_pair(0,-1);
  test.f = make_pair(0,-1);
  test.g = make_pair(0,-1);
  test.h = make_pair(0,-1);

  vector<info> pos = vector<info>(eingabe.size(), test);
  vector<int> last_pos = vector<int>(eingabe.size(),-1);

  vector<int> equal = vector<int>();

  FOR(i, eingabe.size()){
    zuweiser(eingabe[i], pos, last_pos, i);
  }
  if (pos[eingabe.size()-1].c>0 || pos[eingabe.size()-1].d>0 || pos[eingabe.size()-1].e>0 || pos[eingabe.size()-1].f>0 || pos[eingabe.size()-1].g>0 || pos[eingabe.size()-1].h>0){
    cout << "0 1";
  }
  FOR(i, eingabe.size()){
    if(pos[i].a.first==pos[i].b.first){
      DEB(i);
    }
    /*DEB("a: ");
    DEB(pos[i].a.first);
    DEB(pos[i].a.second);
    DEB("b: ");
    DEB(pos[i].b.first);
    DEB(pos[i].b.second);*/
  }
}
