// https://s3.amazonaws.com/codechef_shared/download/Solutions/COOK72/Admin/CHEFLKJ.cpp

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int (i)=(a);(i)<(b);(i)++)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(), (v).end()

typedef vector<int> VI;
typedef long long LL;

const int MAXN = (int) 4e5 + 10;

int a[MAXN];
int n, Q;

unordered_map<int, int> tree[MAXN];

void merge(int k) {
  unordered_map<int, int> &mp1 = tree[2 * k];
  unordered_map<int, int> &mp2 = tree[2 * k + 1];
  unordered_map<int, int> mp;
  for (auto it = mp1.begin(); it != mp1.end(); it++) {
    mp[it->first] += it->second;
  }
  for (auto it = mp2.begin(); it != mp2.end(); it++) {
    mp[it->first] += it->second;
  }
  tree[k] = mp;
}

void build(int k, int lo, int hi) {
  if (lo == hi) {
    unordered_map<int, int> mp;
    mp[a[lo]] = 1;
    tree[k] = mp;
  } else {
    int mid = (lo + hi) / 2;
    build(2 * k, lo, mid);
    build(2 * k + 1, mid + 1, hi);
    merge(k);
  }
}

int getCnt(unordered_map<int, int> &mp, int c) {
  if (mp.find(c) == mp.end()) return 0;
  else return mp[c];
}

int query(int k, int lo, int hi, int left, int right, int val) {
  if (lo == left && hi == right) {
    return getCnt(tree[k], val);
  } else {
    int mid = (lo + hi) / 2;
    int ans = 0;
    if (right <= mid)  ans = query(2 * k, lo, mid, left, right, val);
    else if (left > mid) ans = query(2 * k + 1, mid + 1, hi, left, right, val);
    else {
      int cnt1 = query(2 * k, lo, mid, left, mid, val);
      int cnt2 = query(2 * k + 1, mid + 1, hi, mid + 1, right, val);
      ans = cnt1 + cnt2;
    }
    return ans;
  }
}

void updateVal(unordered_map<int,int> &mp, int oldVal, int newVal) {
  if (mp[oldVal] == 1) mp.erase(oldVal);
  else mp[oldVal]--;
  mp[newVal]++;
}

void update(int k, int lo, int hi, int x, int val) {
  if (lo == hi && lo == x) {
    updateVal(tree[k], a[x], val);
  } else {
    int mid = (lo + hi) / 2;
    if (x <= mid) {
      update(2 * k, lo, mid, x, val);
    }
    else update(2 * k + 1, mid + 1, hi, x, val);
    updateVal(tree[k], a[x], val);
  }
}

int brute(int l, int r, int val) {
  int cnt = 0;
  FOR(i, l, r + 1) if (a[i] == val) cnt++;
  return cnt;
}

const int MAGIC = 300;

int type[MAXN], L[MAXN], R[MAXN];

int main() {
  srand(time(NULL));
  scanf("%d %d", &n, &Q);
  map<int, int> cntMap;
  REP(i, n) {
    scanf("%d", &a[i + 1]);
    cntMap[a[i + 1]]++;
  }
  build(1, 1, n);

unordered_set<int> magicalNumbers;
  REP(i, n) if (cntMap[a[i + 1]] > MAGIC) magicalNumbers.insert(a[i  +1]);
  REP(q, Q) {
    scanf("%d %d %d", &type[q], &L[q], &R[q]);
    int l = L[q], r = R[q];
    if (type[q] == 1) {
      cntMap[r]++;
      if (cntMap[r] > MAGIC) magicalNumbers.insert(r);
    }
  }
  cerr << "goodNumberSize " << magicalNumbers.size() << endl;

  REP(q, Q) {
    int l = L[q], r = R[q];
    if (type[q] == 2) {
      int MAX_ATTEMPS = 20;
      int good = false;
      REP(attempt, MAX_ATTEMPS) {
        int val = l + (rand() % (r - l + 1));
        if (r - l + 1 > 2 * MAGIC && magicalNumbers.find(a[val]) == magicalNumbers.end()) {
          continue;
        }
        int occ = query(1, 1, n, l, r, a[val]);
        if (occ > (r - l + 1) / 2) {
          good = true;
          break;
        }
      }
      puts(good ? "Yes" : "No");
    } else {
      update(1, 1, n, l, r);
      a[l] = r;
    }
  }

  return 0;
}
