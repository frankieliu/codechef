// https://s2.amazonaws.com/codechef_shared/download/Solutions/COOK72/Setter/CHEFLKJ.cpp

#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <set>
#include <map>
#include <complex>
#include <iostream>
#include <time.h>
#include <stack>
#include <stdlib.h>
#include <memory.h>
#include <bitset>
#include <math.h>
#include <string>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

const int MaxN = 1e5 + 10;
const int MOD = 1e9 + 7;
const int INF = 1e9;

struct Fenwick {
  vector < int > where, fenw;
  Fenwick() {
    where.clear();
    fenw.clear();
  }
  Fenwick(const vector < int > &pos) {
    where = pos;
    sort(where.begin(), where.end());
    where.resize(unique(where.begin(), where.end()) - where.begin());
    fenw = vector < int >(where.size(), 0);
  }
  void upd(int pos, int val) {
    pos = lower_bound(where.begin(), where.end(), pos) - where.begin();
    for (int r = pos; r < (int)fenw.size(); r |= r + 1) {
      fenw[r] += val;
    }
  }
  int get(int pos) {
    int res = 0;
    for (int r = pos; r >= 0; r &= r + 1, --r) {
      res += fenw[r];
    }
    return res;
  }
  int get(int l, int r) {
    l = lower_bound(where.begin(), where.end(), l) - where.begin();
    r = upper_bound(where.begin(), where.end(), r) - where.begin() - 1;
    if (l > r) {
      return 0;
    }
    return get(r) - get(l - 1);
  }
};

int n, q, a[MaxN];
map < int, Fenwick > f;
map < int, vector < int > > st;

int rnd(int l, int r) {
  return (1LL * RAND_MAX * rand() + rand()) % (r - l + 1) + l;
}

int main() {
//  freopen("input.txt", "r", stdin);
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    st[a[i]].push_back(i);
  }
  vector < pair < int, pair < int, int > > > queries(q);
  for (int i = 0; i < q; ++i) {
    scanf("%d%d%d", &queries[i].first, &queries[i].second.first, &queries[i].second.second);
    if (queries[i].first == 1) {
      st[queries[i].second.second].push_back(queries[i].second.first);
    }
  }
  for (map < int, vector < int > > :: iterator it = st.begin(); it != st.end(); ++it) {
    f.insert(f.end(), make_pair(it->first, Fenwick(it->second)));
  }
  for (int i = 1; i <= n; ++i) {
    f[a[i]].upd(i, +1);
  }
  for (int it = 0; it < q; ++it) {
    int type = queries[it].first;
    int x = queries[it].second.first;
    int y = queries[it].second.second;
    if (type == 1) {
      f[a[x]].upd(x, -1);
      a[x] = y;
      f[a[x]].upd(x, +1);
    } else {
      bool ok = false;
      for (int i = 0; i < 25 && !ok; ++i) {
        int w = a[rnd(x, y)];
        if (f[w].get(x, y) > (y - x + 1) / 2) {
          ok = true;
        }
      }
      printf(ok == true ? "Yes\n" : "No\n");
    }
  }
  return 0;
}

