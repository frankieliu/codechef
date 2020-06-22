#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

int main(){
  int lines;
  cin >> lines;

  int s1,s2;
  int c1=0, c2=0;
  int rmax1=0, rmax2=0;
  for(int i=0;i<lines;i++){
    cin >> s1 >> s2;
    c1 += s1;
    c2 += s2;
    if (c1 > c2)
      rmax1 = std::max(rmax1,(c1-c2));
    else
      rmax2 = std::max(rmax2,(c2-c1));
  }
  cout << ((rmax1>rmax2)?1:2) << " " <<
    ((rmax1>rmax2)?rmax1:rmax2) << endl;
}
