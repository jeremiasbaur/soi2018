#include <bits/stdc++.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)
#define DEB(x) //cerr << x << "\n"

struct Node{
  int pos, value;
};

int tents;

void build(vector<Node>& segtree, vector<int>& n_array, int node, int left, int right){
  if (left == right){
    segtree[node].value = n_array[left];
    segtree[node].pos = left;
  }
  else{
    int mid = (left+right)/2;
    build(segtree, n_array, node*2, left, mid);
    build(segtree, n_array, node*2+1, mid+1, right);
    segtree[node].value = max(segtree[node*2].value,segtree[node*2+1].value);
  }
}

void update(vector<Node>& segtree, int node, int left, int right, int n_pos, int new_val){
  if (left == right){
    segtree[node].value = new_val;
  }
  else{
    int mid = (left+right)/2;
    if (n_pos <= mid){
      update(segtree, 2*node, left, mid, n_pos, new_val);
    }
    else{
      update(segtree, 2*node+1, mid+1, right, n_pos, new_val);
    }
    segtree[node].value = max(segtree[node*2].value,segtree[node*2+1].value);
  }
}

int get_max(vector<Node>& segtree, int node, int left, int right, int range_left, int range_right){
  //usleep(10000);
  //cout << node << " " << left << " " << right << " " << range_left << " " << range_right << "\n";
  if (range_left>range_right){
    return 0;
  }
  if (left == range_left && right == range_right){
    return segtree[node].value;
  }
  int mid = (left+right)/2;
  return max(get_max(segtree, node*2, left, mid, range_left, min(range_right, mid)),
             get_max(segtree, node*2+1, mid+1, right, max(range_left, mid+1), range_right));
}

int get_pos(vector<Node>& segtree, int node, int left, int right, int value){
  if (left == right){
    if (segtree[node].value <= value){
      return tents+1;
    }
    return segtree[node].pos;
  }
  else{
    DEB("new start: ");
    int mid = (left+right)/2;
    if (segtree[node*2].value>value){
      DEB(segtree[node*2].value);
      return get_pos(segtree, node*2, left, mid, value);
    } else {
      DEB(segtree[node*2+1].value);
      return get_pos(segtree, node*2+1, mid+1, right, value);
    }
  }
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int queries, a, b;
  cin >> tents >> queries;

  vector<int> platz = vector<int>(tents, 0);
  vector<Node> segtree = vector<Node>(tents*4);

  FOR(i, tents){
    cin >> a;
    platz[i] = a;
  }

  build(segtree, platz, 1, 0, tents-1);

  FOR(i, queries){
    cin >> a;
    if (a==1){
      cin >> a >> b;
      update(segtree, 1, 0, tents-1, a, b);
    } else{
      cin >> a;
      a = get_pos(segtree, 1, 0, tents-1, a-1);
      if (a==tents+1){
        cout << tents << "\n";
      } else{
        cout << a << "\n";
      }
      DEB(tents);
    }

  }
}
