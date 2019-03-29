#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class Point
{
public: 
  Point(int x, int y) : x_(x), y_(y) {}
  Point() : x_(0), y_(0) {}

  static bool OrderByX(const Point& left, const Point& right) {
    return left.x_ < right.x_;
  }

  static bool OrderByY(const Point& left, const Point& right) {
    return left.y_ < right.y_;
  }

  int x_;
  int y_;
};

float Distance(const Point& left, const Point& right) {
  return sqrt(pow(left.x_ - right.x_, 2) + pow(left.y_ - right.y_, 2));
}
int NearestPoints(const std::vector<Point>& points, int start, int end, Point* point1, Point* point2) {
  if (end > start) {
  int middle = (start + end) / 2;
  int left_min_distance = NearestPoints(points, start, middle, point1, point2);
  int right_min_distance = NearestPoints(points, middle + 1, end, point1, point2);
  int min_distance = left_min_distance > right_min_distance ? right_min_distance : left_min_distance;
  std::vector<Point> left_part_points;

  for (int i = start; i <= middle; ++i) {
    if (points[middle].x_ - points[i].x_ <= min_distance) {
      left_part_points.push_back(points[i]);
    }
  }

  sort(left_part_points.begin(), left_part_points.end(), Point::OrderByY);
  std::vector<Point> right_part_points;

  for (int i = middle + 1; i <= end; ++i) {
    if (points[i].x_ - points[middle].x_ <= min_distance) {
      right_part_points.push_back(points[i]);
    }
  }

  sort(right_part_points.begin(), right_part_points.end(), Point::OrderByY);

  int distance_y = 0;
  int point_distance = 0;

  for(int i = 0; i < left_part_points.size(); ++i) {
    for(int j = 0; j < right_part_points.size(); ++j) {
      distance_y = left_part_points[i].y_ > right_part_points[j].y_ ? left_part_points[i].y_ - right_part_points[j].y_ :
                   right_part_points[j].y_ - left_part_points[i].y_;

      if (distance_y <= min_distance) {
        point_distance = Distance(left_part_points[i], right_part_points[j]);

        if (point_distance < min_distance) {
          min_distance = point_distance;

          *point1 = left_part_points[i];
          *point2 = right_part_points[j];
        }
      }
    }
  }

  return min_distance;
  } else {
    return 0x7FFFFFFF;
  }
}
  
    
int main(int argc, char** argv) {
  std::vector<Point> points;

  points.push_back(Point(1,3));
  points.push_back(Point(1,2));
  points.push_back(Point(3,8));
  points.push_back(Point(5,6));
  points.push_back(Point(4,1));

  sort(points.begin(), points.end(), Point::OrderByX);

  Point point1;
  Point point2;
  NearestPoints(points, 0, points.size() - 1, &point1, &point2);

  cout << "距离最短的两点是 " << endl;
  printf("Point1: (%d, %d) <--> Point2: (%d, %d)\n", point1.x_, point1.y_, point2.x_, point2.y_);
  cout << "他们的距离是 " << Distance(point1, point2);
}