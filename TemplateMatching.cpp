#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;


int main(int argc, char**argv){

  vector<Mat> img;

  for(int i =1; i < argc; i++){
    img.push_back(imread(argv[i], 1));
  }
  img.push_back(imread(argv[1], 1));



  matchTemplate(img[0],img[1], img[2],TM_CCORR);
  normalize( img[2], img[2], 0, 1, NORM_MINMAX, -1, Mat() );
  



  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( img[2], &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  matchLoc = minLoc;

  rectangle( img[0], matchLoc, Point( matchLoc.x + img[1].cols , matchLoc.y + img[1].rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( img[2], matchLoc, Point( matchLoc.x + img[1].cols , matchLoc.y + img[1].rows ), Scalar::all(0), 2, 8, 0 );

  imshow("Image", img[0]);
  imshow("Template", img[1]);
  imshow("Image Matched", img[2]);

   waitKey(0);                                       
    return 0;
  

}
