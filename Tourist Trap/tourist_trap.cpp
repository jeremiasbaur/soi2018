#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m) for(int i = 0; i < m; i ++)

struct street{

  bool operator<(const street& a) const{
    if (x == a.x){
      return y < a.y;
    }
    else {
      return x < a.x;
    }
  }
};

struct end_x{
  bool operator()(const street& a, const street& b) const {
    return a.x + a.width < b.x + b.width;
  }
};

street create_street(int x, int y, int width, int height, int node_id){
  street new_street;
  new_street.x = x;
  new_street.y = y;
  new_street.width = width;
  new_street.height = height;
  new_street.node_id = node_id;
  return new_street;
}

multimap<int, pair<int,int>> insert_rectangle(multimap<int, pair<int,int>>& interval_tree, street& street_to_insert){
  interval_tree.insert(make_pair(street_to_insert.y + street_to_insert.height, make_pair(street_to_insert.node_id, 0)));
  interval_tree.insert(make_pair(street_to_insert.y, make_pair(street_to_insert.node_id, 1)));
  return interval_tree;
}

multimap<int, pair<int,int>> delete_rectangle(multimap<int, pair<int,int>>& interval_tree, street& street_to_delete){
  vector<pair<int, pair<int,int>>> saver;
  int counter = 0;

  auto equal_range = interval_tree.equal_range(street_to_delete.y);
  for(auto& it = equal_range.first; it!=equal_range.second; ++it){
    cout << "test 1_1";
    if (it->second.first != street_to_delete.node_id){
      cout << "test 1";
      saver.push_back(make_pair(it->first, make_pair(it->second.first, it->second.second)));
      counter++;
    }
  }
  equal_range = interval_tree.equal_range(street_to_delete.y + street_to_delete.height);
  for(auto& it = equal_range.first; it!=equal_range.second; ++it){
    cout << "test 2_1";
    if (it->second.first != street_to_delete.node_id){
      cout << "test 2";
      saver.push_back(make_pair(it->first, make_pair(it->second.first, it->second.second)));
      counter++;
    }
  }
  interval_tree.erase(street_to_delete.y);
  interval_tree.erase(street_to_delete.y + street_to_delete.height);
  FOR(i, counter){
    interval_tree.insert(saver[i]);
  }
  return interval_tree;
}

int main(){
  int cases, x, y, width, height, count_streets;
  cin >> cases;

  FOR(i, cases){
    cin >> width >> height >> x >> y >> count_streets; // width and height are multimap size and x and y are stoffles coordinates
    vector<street> streets;
    vector<street> sorted_streets_start;
    vector<street> sorted_streets_end;

    FOR(j, count_streets){
      street current_street;
      cin >> current_street.x >> current_street.y >> current_street.width >> current_street.height;
      current_street.node_id = j;
      streets.push_back(current_street);
      sorted_streets_start.push_back(current_street);
      sorted_streets_end.push_back(current_street);
    }

    sort(sorted_streets_start.begin(), sorted_streets_start.end());
    sort(sorted_streets_end.begin(), sorted_streets_end.end(), end_x());

    multimap<int,street> active_rectangle_set;

    multimap<int, pair<int,int>> interval_tree; // y value as key, pair(index, y_top -> 0 / y_bot -> 1)
    street test_street1 = create_street(0, 1, 1, 4, 0);
    street test_street2 = create_street(0, 3, 1, 5, 1);
    street test_street3 = create_street(0, 1, 1, 4, 3);
    interval_tree = insert_rectangle(interval_tree, test_street1);
    interval_tree = insert_rectangle(interval_tree, test_street2);
    interval_tree = insert_rectangle(interval_tree, test_street3);

    for(multimap<int, pair<int,int>>::iterator it=interval_tree.lower_bound(1); it!=interval_tree.upper_bound(10); ++it){
      cout << it->first << " => " << it->second.first << '\n';
    }

    interval_tree = delete_rectangle(interval_tree, test_street1);
    for(multimap<int, pair<int,int>>::iterator it=interval_tree.lower_bound(1); it!=interval_tree.upper_bound(10); ++it){
      cout << it->first << " => " << it->second.first << '\n';
    }
  }
}
