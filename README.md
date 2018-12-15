Project at it's currrent state

There are 3 seperate functionalities, that I was unable to fully integrate.

Challenges:
Integrating Gazebo/ROS into the project as I started by devloping my HMI is pure OpenCV 3.2 and MCL as a standalone C++ class.

Once those were at a stable state I began Integrating Gazebo/ROS which didnt work well with my pre-existing codebase require a good amount of refactoring, which lead me to the point im currently at. 



Function one: Human Machine Interface
Location: ros/src/HMI
Files: TemplateMatching.cpp TemplateMatching.h and CMakeLists.txt



Execution: 3 images are required, and will be passed in as command line arguments

1: your drawn map
2: the template for objects
3: the template for the robot

 

