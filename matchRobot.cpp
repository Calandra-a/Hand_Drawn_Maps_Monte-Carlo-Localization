#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;


int match_method;
/// Global Variables
Mat img; Mat templ; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int main( int, char** argv )
{
  /// Load image and template
  img = imread( argv[1], 1 );
  templ = imread( argv[2], 1 );
  
  /// Create windows
  namedWindow( image_window, WINDOW_AUTOSIZE );
  //namedWindow( result_window, WINDOW_AUTOSIZE );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, CV_TM_CCORR_NORMED );
  normalize( result, result, 1, 2, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  Point minLoc; Point maxLoc;
  Point matchLoc;
  double minVal; double maxVal;

    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    result.at<float>(minLoc.x,minLoc.y)=1.0;
    result.at<float>(maxLoc.x,maxLoc.y)=0.0;

    ///the best matches are higher values
    matchLoc = maxLoc;

    /// Show me what you got
    rectangle( img, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ),
     Scalar::all(100), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ),
     Scalar::all(0), 2, 8, 0 );

    Point bottom;
    bottom.x = matchLoc.x + templ.cols;
    bottom.y = matchLoc.y + templ.rows;

    Point pose;
    pose.x = (matchLoc.x +bottom.x)/2;
    pose.y = (matchLoc.y+bottom.y)/2;



  imshow( image_window, img );
  //imshow( result_window, result );
  
  waitKey(0);
  return 0;
}
