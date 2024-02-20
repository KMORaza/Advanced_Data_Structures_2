#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  
    return (val > 0) ? 1 : 2; 
}
bool compare(Point anchor, Point p1, Point p2) {
    int o = orientation(anchor, p1, p2);
    if (o == 0) 
        return (p1.x + p1.y) < (p2.x + p2.y);
    return (o == 2);
}
vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return points; 
    int anchorIndex = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[anchorIndex].y || (points[i].y == points[anchorIndex].y && points[i].x < points[anchorIndex].x)) {
            anchorIndex = i;
        }
    }
    swap(points[0], points[anchorIndex]);
    sort(points.begin() + 1, points.end(), [points](Point p1, Point p2) {
        return compare(points[0], p1, p2);
    });
    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);
    for (int i = 3; i < n; i++) {
        while (orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    return hull;
}
int main() {
    vector<Point> points = { {0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    cout << "Available Coordinates = ";
    for (const Point& p : points) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    vector<Point> convexHullPoints = convexHull(points);
    cout << "\nHull Coordinates = ";
    for (const Point& p : convexHullPoints) {
        cout << "(" << p.x << ", " << p.y << ") ";
    }
    return 0;
}
