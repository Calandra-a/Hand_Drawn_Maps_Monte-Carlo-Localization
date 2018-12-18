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
	int range;
	int bearing; //degrees?
	int signiture; //signiture 
	int correspondence;
public:
	void setLocation(Point,Point);
	void setrbs();
	void getObject();
};

class mMap{
private:
  Point mapSize[2];

public:
  vector<object> objects;
  void setObject(object);
  void setMapSize(Point, Point);
  void printMap();
};

vector<feature> match( Mat , Mat );

mMap mapNorm(mMap);

Point robotMatch (Mat,Mat);

feature convert (object, int,int);
