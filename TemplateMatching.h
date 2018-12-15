#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;
using namespace cv;
class object{
public:
  Point topLeft;
  Point bottomRight;
public:
  void setLocation(Point,Point);
  void getObject();
};
class map{
private:
  Point mapSize[2];
public:
  vector<object> objects;
  void setObject(object);
  void setMapSize(Point, Point);
  void printMap();
};
map match( Mat , Mat );
map mapNorm(map);
Point robotMatch (Mat,Mat);