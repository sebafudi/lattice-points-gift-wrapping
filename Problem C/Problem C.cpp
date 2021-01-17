#include <math.h>

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
#define ll long long
#define ld long double

int orientation(pair<ll, ll> p, pair<ll, ll> q, pair<ll, ll> r) {
  ll val = (q.second - p.second) * (r.first - q.first) -
           (q.first - p.first) * (r.second - q.second);
  if (val == 0) return 0;
  return (val > 0) ? 1 : 2;
}

void convexHull(vector<pair<ll, ll>>& points) {
  int n = points.size();
  if (n < 3) return;
  vector<pair<ll, ll>> hull;
  int l = 0;
  for (int i = 1; i < n; i++)
    if (points[i].first < points[l].first) l = i;
  int p = l, q;
  do {
    hull.push_back(points[p]);
    q = (p + 1) % n;
    for (int i = 0; i < n; i++) {
      if (orientation(points[p], points[i], points[q]) == 2) q = i;
    }
    p = q;
  } while (p != l);
  points = hull;
}

ld polygonArea(vector<pair<ll, ll>> A) {
  ld area = 0;
  for (size_t i = 2; i < A.size(); i++)
    area += (A[i].first - A[0].first) * (A[i - 1].second - A[0].second) -
            (A[i].second - A[0].second) * (A[i - 1].first - A[0].first);
  return fabs(area / 2);
}

ll gcd(ll a, ll b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

ll boundary(vector<pair<ll, ll>> A) {
  ll total_points = A.size();
  for (size_t i = 0; i < A.size(); i++) {
    ll distance_x = abs(A[i].first - A[(i + 1) % A.size()].first);
    ll distance_y = abs(A[i].second - A[(i + 1) % A.size()].second);
    total_points += static_cast<ll>(gcd(distance_x, distance_y)) - 1;
  }
  return total_points;
}

int main() {
  int number = 0;
  cin >> number;
  for (int i = 0; i < number; i++) {
    int sides = 0;
    vector<pair<ll, ll>> points;
    cin >> sides;
    for (int i = 0; i < sides; i++) {
      int a, b;
      cin >> a >> b;
      points.push_back(make_pair(a, b));
    }
    convexHull(points);

    ll lattice_points = 0;
    lattice_points =
        static_cast<ll>(-boundary(points) / 2. + polygonArea(points) + 1);
    // Wzór Picka
    cout << lattice_points << endl;
  }
  return 0;
}