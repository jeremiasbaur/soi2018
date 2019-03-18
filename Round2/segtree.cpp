#include <bits/stdc++.h>
//#include <unistd.h>
using namespace std;

#define int long long
#define FOR(i,m) for(int i = 0; i < m ; i++)

void build(vector<int>& segtree, vector<int>& n_array, int node, int left, int right){
  if (left == right){
    segtree[node] = n_array[left];
  }
  else{
    int mid = (left+right)/2;
    build(segtree, n_array, node*2, left, mid);
    build(segtree, n_array, node*2+1, mid+1, right);
    segtree[node] = max(segtree[node*2],segtree[node*2+1]);
  }
}

void update(vector<int>& segtree, int node, int left, int right, int n_pos, int new_val){
  if (left == right){
    segtree[node] = new_val;
  }
  else{
    int mid = (left+right)/2;
    if (n_pos <= mid){
      update(segtree, 2*node, left, mid, n_pos, new_val);
    }
    else{
      update(segtree, 2*node+1, mid+1, right, n_pos, new_val);
    }
    segtree[node] = max(segtree[node*2],segtree[node*2+1]);
  }
}

int get_max(vector<int>& segtree, int node, int left, int right, int range_left, int range_right){
  //usleep(10000);
  //cout << node << " " << left << " " << right << " " << range_left << " " << range_right << "\n";
  if (range_left>range_right){
    return 0;
  }
  if (left == range_left && right == range_right){
    return segtree[node];
  }
  int mid = (left+right)/2;
  return max(get_max(segtree, node*2, left, mid, range_left, min(range_right, mid)),
             get_max(segtree, node*2+1, mid+1, right, max(range_left, mid+1), range_right));
}

signed main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int numbers, queries;
  cin >> numbers >> queries;

  vector<int> n_array = vector<int>(numbers,0);
  FOR(i, numbers){
    int number;
    cin >> number;
    n_array[i] = number;
  }

  vector<int> segtree = vector<int>(4*numbers,0);
  build(segtree, n_array, 1, 0, numbers-1);

  FOR(i, queries){
    string type; int a,b;
    cin >> type >> a >> b;
    if (type == "set"){
      update(segtree, 1, 0, numbers-1, a, b);
    }
    else{
      cout << get_max(segtree, 1, 0, numbers-1, a, b) << "\n";
    }
  }

}
