#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m) for(int i = 0; i < m; i ++)

struct street{
  int x, y, width, height, node_id, friend_id;
  set<int> overlaps;

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

void insert_rectangle(multimap<int, pair<int,int>>& interval_tree, street& street_to_insert){
  interval_tree.insert(make_pair(street_to_insert.y + street_to_insert.height, make_pair(street_to_insert.node_id, 0)));
  interval_tree.insert(make_pair(street_to_insert.y, make_pair(street_to_insert.node_id, 1)));
  //return interval_tree;
}

multimap<int, pair<int,int>> delete_rectangle(multimap<int, pair<int,int>>& interval_tree, street& street_to_delete){
  vector<pair<int, pair<int,int>>> saver;
  int counter = 0;

  auto equal_range = interval_tree.equal_range(street_to_delete.y);
  for(auto& it = equal_range.first; it!=equal_range.second; ++it){
    //cout << "test 1_1";
    if (it->second.first != street_to_delete.node_id){
      //cout << "test 1";
      saver.push_back(make_pair(it->first, make_pair(it->second.first, it->second.second)));
      counter++;
    }
  }
  equal_range = interval_tree.equal_range(street_to_delete.y + street_to_delete.height);
  for(auto& it = equal_range.first; it!=equal_range.second; ++it){
    //cout << "test 2_1";
    if (it->second.first != street_to_delete.node_id){
      //cout << "test 2";
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

void overlaping_rectangles(multimap<int, pair<int,int>>& interval_tree, street& street_to_look, vector<street>& streets){
  int x,y,x_width,y_height;
  x = street_to_look.x-1;
  x_width = street_to_look.x + street_to_look.width;
  y = street_to_look.y-1;
  y_height = street_to_look.y + street_to_look.height;

  multimap<int,int> checker;

  for (multimap<int, pair<int,int>>::iterator it=interval_tree.begin(); it!=interval_tree.upper_bound(street_to_look.y+street_to_look.height); ++it){
    street& iterator_street = streets[it->second.first];
    if (iterator_street.y+iterator_street.height-1 < y){
      continue;
    }
    if ((iterator_street.x+iterator_street.width-1 == x && iterator_street.y + iterator_street.height-1 == y)
      || (iterator_street.x == x_width && iterator_street.y + iterator_street.height == y)
      || (iterator_street.x == x_width && iterator_street.y == y_height)
      || (iterator_street.x+iterator_street.width-1 == x && iterator_street.y == y_height)){
        //cout << "don't overlap: " << street_to_look.node_id << " and " << iterator_street.node_id << "\n";
        continue;
      }
    //cout << "overlap: " << street_to_look.node_id << " and " << iterator_street.node_id << "\n";
    street_to_look.overlaps.insert(it->second.first);
    streets[it->second.first].overlaps.insert(street_to_look.node_id);
  }
}

bool bfs(pair<int, bool>const& stoffles_street, vector<street>const& streets, set<int>const& edge_streets){
  deque<int> unvisited;
  set<int> visited;
  visited.insert(stoffles_street.first);
  for(auto const& it:streets[stoffles_street.first].overlaps){
    unvisited.push_back(it);
  }
  while(unvisited.size()!=0){
    int street_index = unvisited.front();
    unvisited.pop_front();
    if (visited.find(street_index)!=visited.end()){
      continue;
    }
    if (edge_streets.find(street_index)!=edge_streets.end()){
      return true;
    }
    visited.insert(street_index);
    for(auto const& it:streets[street_index].overlaps){
      unvisited.push_back(it);
    }
  }
  return false;
}

int main(){
  ifstream cin("touristtrap-sub4-attempt0.txt");
  ofstream cout("output.txt");
  int cases, x, y, width, height, count_streets, tester;
  cin >> cases;
  tester = 7;
  bool tester_bool = false;

  FOR(i, cases){
    printf("Case %d\n", i);
    cin >> width >> height >> x >> y >> count_streets; // width and height are multimap size and x and y are stoffles coordinates
    vector<street> streets;
    multimap<int,street> sorted_streets_start;
    multimap<int,street> sorted_streets_end;
    pair<int, bool> stoffles_street = make_pair(0, false);
    set<int> edge_streets;

    if (tester_bool && i == tester){
      cout << width << " " << height << " " << x << " " << y << " " << count_streets << "\n";
    }

    FOR(j, count_streets){
      street current_street;
      cin >> current_street.x >> current_street.y >> current_street.width >> current_street.height;
      current_street.node_id = j;
      streets.push_back(current_street);
      sorted_streets_start.insert(make_pair(current_street.x, current_street));
      sorted_streets_end.insert(make_pair(current_street.x+current_street.width +1 , current_street));
      if (tester_bool && i==tester){
        cout << current_street.x << " " << current_street.y << " " << current_street.width << " " << current_street.height << "\n";
      }
      if((current_street.x == 0 || current_street.x + current_street.width == width) || (current_street.y == 0 || current_street.y + current_street.height == height)){
        edge_streets.insert(current_street.node_id);
      }

      if (!stoffles_street.second && (current_street.x <= x && current_street.x + current_street.width-1 >= x) && (current_street.y <= y && current_street.y + current_street.height-1 >= y)){
        stoffles_street.first = current_street.node_id;
        stoffles_street.second = true;
      }
    }

    if ((x==0 || x == width-1) || (y == 0 || y == height-1) || edge_streets.find(stoffles_street.first)!=edge_streets.end()){
      cout << "Case #" << i << ": POSSIBLE\n";
      continue;
    }

    multimap<int,street> active_rectangle_set;

    multimap<int, pair<int,int>> interval_tree; // y value as key, pair(index, y_top -> 0 / y_bot -> 1) FAKE INTERVAL TREE LOL

    int x = 0;
    int last = 0;
    while (sorted_streets_start.lower_bound(x)!=sorted_streets_start.end()){ // iterator through whole start events
      auto it_value = sorted_streets_start.lower_bound(x); // get iterator at with current x key
      int current_x = it_value->first; // get current x
      x = it_value->first +1; // next x is current x + 1

      while (sorted_streets_end.lower_bound(last)!=sorted_streets_end.upper_bound(x-1)){
        auto it_value_end = sorted_streets_end.lower_bound(last);
        int current_end_x = it_value_end->first;
        if (current_end_x <= x-1){
          auto it_at_end_value = sorted_streets_end.equal_range(current_end_x);
          for(auto& it = it_at_end_value.first; it != it_at_end_value.second; ++it){
            interval_tree = delete_rectangle(interval_tree, streets[it->second.node_id]);
            //cout << "deleted " << it->second.node_id << " at " << x-1 << "\n";
          }
        }
        last = it_value_end->first +1;
      }

      auto it_at_value = sorted_streets_start.equal_range(current_x); // get iterator for elements with current x key

      for(auto& it = it_at_value.first; it != it_at_value.second; ++it){ // iterate through elements with current x key
        insert_rectangle(interval_tree, streets[it->second.node_id]); // insert them in interval_tree
        overlaping_rectangles(interval_tree, streets[it->second.node_id], streets); // look for overlaps
        //cout << "inserted " << it->second.node_id << " at " << x-1 << "\n";
      }

      while (sorted_streets_end.lower_bound(last)!=sorted_streets_end.upper_bound(x-1)){
        auto it_value_end = sorted_streets_end.lower_bound(last);
        int current_end_x = it_value_end->first;
        if (current_end_x < x){
          auto it_at_end_value = sorted_streets_end.equal_range(current_end_x);
          for(auto& it = it_at_end_value.first; it != it_at_end_value.second; ++it){
            interval_tree = delete_rectangle(interval_tree, streets[it->second.node_id]);
            //cout << "deleted " << it->second.node_id << " at " << x-1 << "\n";
          }
        }
        last = it_value_end->first +1;
      }
    }
    if (tester_bool && i == tester){
      FOR(j, count_streets){
        cout << "street " << j << " is connected with: ";
        for(auto const& it:streets[j].overlaps){
          cout << it << " ";
        }
        cout << "\n";
      }
    cout << "Stoffles Street: " << stoffles_street.first << "\n";
    }

    if (edge_streets.size()==0 || !bfs(stoffles_street, streets, edge_streets)){
      cout << "Case #" << i << ": IMPOSSIBLE\n";
    } else{
      cout << "Case #" << i << ": POSSIBLE\n";
    }
  }
}
