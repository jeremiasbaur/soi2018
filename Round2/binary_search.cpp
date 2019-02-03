#include <bits/stdc++.h>
using namespace std;

#define in long long
#define FOR(i,m) for(in i = 0; i < m ; i++)

signed main(){
  in width, height, max_queries;
  cin >> width >> height >> max_queries;

  if (height == 1){ // if heihgt == 1 -> normal binary search
    FOR(i,height){
      in mid, right, left, answer;
      right = width-1;
      left = 0;
      while(left<=right){
        mid = (left + right)/2;
        cout << "q " << mid << " " << i << endl;
        cin >> answer;
        if (answer==1337){
          break;
        } else if (answer < 1337){
          right = mid - 1;
        } else{
          left = mid + 1;
        }
      }
      if (answer==1337){
        cout  << "s " << (left + right)/2 << " " << i << endl;
        break;
      } else if (height == 1 || height == i+1){
        cout << "no solution" << endl;
      }
    }
  }
  else { // if height > 1 -> no need for binary search because limits allow "stair search"
    in x, y, answer;
    x = 0;
    y = 0;
    while (true){
      cout  << "q " << x << " " << y << endl;
      cin >> answer;
      if (answer==1337){
        cout  << "s " << x << " " << y << endl;
        break;
      }
      if (answer>1337 && x+1<width){
        x++;
      } else if (y+1<height){
        y++;
      } else{
        cout << "no solution" << endl;
        break;
      }
    }
  }
}
