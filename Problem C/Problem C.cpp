#include <math.h>

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
#define ll long long
#define ld long double

int Orientation(pair<ll, ll> point, pair<ll, ll> vector1, pair<ll, ll> vector2) {
  ll val = (vector1.second - point.second) * (vector2.first - vector1.first) -
           (vector1.first - point.first) * (vector2.second - vector1.second);
  if (val == 0) return 0;
  return (val > 0) ? 1 : 2;
}

void ConvexHull(vector<pair<ll, ll>>& points) {
  int points_count = points.size();
  if (points_count < 3) return;
  vector<pair<ll, ll>> hull;
  int first_point = 0;

  // Find lower left point
  for (int i = 1; i < points_count; i++)
    if (points[i].first < points[first_point].first) first_point = i;

  int current_point = first_point, next_point;
  do {
    hull.push_back(points[current_point]);
    next_point = (current_point + 1) % points_count;
    for (int current_ccw_most = 0; current_ccw_most < points_count; current_ccw_most++) {
      if (Orientation(points[current_point], points[current_ccw_most], points[next_point]) ==
          2)
        next_point = current_ccw_most;
    }
    current_point = next_point;
  } while (current_point != first_point);
  points = hull;
}

ld PolygonArea(vector<pair<ll, ll>> A) {
  ld area = 0;
  for (size_t i = 2; i < A.size(); i++)
    area += (A[i].first - A[0].first) * (A[i - 1].second - A[0].second) -
            (A[i].second - A[0].second) * (A[i - 1].first - A[0].first);
  return abs(area / 2);
}

ll GreatestCommonDivisor(ll a, ll b) {
  if (b == 0) return a;
  return GreatestCommonDivisor(b, a % b);
}

ll Boundary(vector<pair<ll, ll>> A) {
  ll total_points = A.size();
  for (size_t i = 0; i < A.size(); i++) {
    ll distance_x = abs(A[i].first - A[(i + 1) % A.size()].first);
    ll distance_y = abs(A[i].second - A[(i + 1) % A.size()].second);
    total_points +=
        static_cast<ll>(GreatestCommonDivisor(distance_x, distance_y)) - 1;
  }
  return total_points;
}

int main() {
  int number_of_tests = 0;
  cin >> number_of_tests;
  for (int i = 0; i < number_of_tests; i++) {
    int number_of_points = 0;
    vector<pair<ll, ll>> points;
    cin >> number_of_points;
    for (int i = 0; i < number_of_points; i++) {
      int a, b;
      cin >> a >> b;
      points.push_back(make_pair(a, b));
    }
    ConvexHull(points);

    ll lattice_points = 0;
    // Pick's theorem
    lattice_points =
        static_cast<ll>(-Boundary(points) / 2. + PolygonArea(points) + 1);
    cout << lattice_points << endl;
  }
  return 0;
}