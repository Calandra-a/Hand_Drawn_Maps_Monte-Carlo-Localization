#include "TemplateMatching.h"

/// Global Variables
Mat img; Mat templ; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int main(int, char** argv){
 Mat img = imread( argv[1], 1 );
 Mat templ = imread( argv[2], 1 );
 Mat templ2 = imread(argv[3],1);
 match(img, templ);
 robotMatch(img,templ2);

}

map match( Mat img, Mat templ)
{
  /// Load image and template
 // img = imread( argv[1], 1 );
  //templ = imread( argv[2], 1 );
  //Create Map
  map Map;
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

  for(int k=1;k<=20;k++){
    object obj;
    minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
    result.at<float>(minLoc.x,minLoc.y)=1.0;
    result.at<float>(maxLoc.x,maxLoc.y)=0.0;

    ///the best matches are higher values
    matchLoc = maxLoc;

    /// Show me what you got
    rectangle( img, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ),
     Scalar::all(0), 2, 8, 0 );
    rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ),
     Scalar::all(0), 2, 8, 0 );
    Point bottom;
    bottom.x = matchLoc.x + templ.cols;
    bottom.y = matchLoc.y + templ.rows;
    
    //creates object from template match
    obj.setLocation(matchLoc,bottom);
    //sets object in map
    Map.setObject(obj);

    //printf("TOP: X: %d Y: %d\n", matchLoc.x, matchLoc.y);
    //printf("BOTTOM: X: %d Y: %d\n", bottom.x, bottom.y);
  }
  Map = mapNorm(Map);
  Map.printMap();
  
  //imshow( image_window, img );
  //imshow( result_window, result );
  
  //waitKey(0);
  return Map;
}

Point robotMatch( Mat img, Mat templ )
{
  /// Load image and template
  //img = imread( argv[1], 1 );
  //templ = imread( argv[2], 1 );
  
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
  return pose;
}


//Object class
void object::setLocation(Point topLeft,Point bottomRight){
  this -> topLeft =  topLeft;
  this -> bottomRight = bottomRight;
}
void object::getObject(){
  printf("\tX: %d Y:%d\n",topLeft.x,topLeft.y);
  printf("\tX: %d Y:%d\n",bottomRight.x,bottomRight.y);
}

//Map class
void map::setMapSize(Point topLeft, Point bottomRight){
  mapSize[0] = topLeft;
  mapSize[1] = bottomRight;
}

void map::setObject(object obj){
  objects.push_back(obj);
}

void map::printMap(){
  for (int i =0; i<objects.size(); i++){
    printf("Object: %d\n",i);
    objects.at(i).getObject();


  }
}


map mapNorm(map Map){
  vector<int> remove;
  map newMap;
  for(int i = 0; i < Map.objects.size(); i++){
    for(int j = 1; j < Map.objects.size(); j++){

if (((abs(Map.objects.at(i).topLeft.x - Map.objects.at(j).topLeft.x) < 4) &&
          (abs(Map.objects.at(i).topLeft.y - Map.objects.at(j).topLeft.y) < 4) &&
          (abs(Map.objects.at(i).bottomRight.x - Map.objects.at(j).bottomRight.x) < 4) &&
          (abs(Map.objects.at(i).bottomRight.y - Map.objects.at(j).bottomRight.y) < 4)) && 
          (i!=j) &&
          (find(remove.begin(),remove.end(),j) == remove.end())){

            remove.push_back(i);
      
      }
    }
  }
  for (int i =0; i < Map.objects.size(); i++){
    if(find(remove.begin(),remove.end(),i) == remove.end()){
      newMap.objects.push_back(Map.objects.at(i));
    }
  }
  return newMap;
}
