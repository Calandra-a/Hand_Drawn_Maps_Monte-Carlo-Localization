Project at it's currrent state

There are 3 seperate functionalities, that I was unable to fully integrate.

Challenges:
Integrating Gazebo/ROS into the project as I started by devloping my HMI is pure OpenCV 3.2 and MCL as a standalone C++ class.

Once those were at a stable state I began Integrating Gazebo/ROS which didnt work well with my pre-existing codebase and required a good amount of refactoring which paired with


Function one: Human Machine Interface
File: TemplateMatching.cpp
 mapMatch
Developed using OpenCV 3.2


Example execution command: 
./mapMatch testing/map_full.png testing/template.png testing/template_robot.png

Execution: 3 images are required, and will be passed in as command line arguments

1: your drawn map
2: the template for objects
3: the template for the robot


I have pre made testing documents in the testing folder as well

Images should be passed in in the order of MAP, OBJECT TEMPLATE, ROBOT TEMPLATE.


Function two: MCL
File: mcl.cpp
Comiled Executable: mcl

Execution command:
./mcl

output: since it isnt hooked up to gazebo I have a generated set of starting particles display textually.

Then display the resampled particles after one iteration of the algorithm 

The outputs consists of each particles, x,y,and rotation posisiton(t) 

and the resampled set also displays it's weights.



 

These are compiled using cmake 2.8 or above

compile commands:

$cmake .
$make

then execute the corresponding executable



Finally,
There is the gazebo models with the created worlds for testing once the project is fully functional.

this is located in the Gazebo folder.

To compile:

run catkin_make in the Gazebo folder

to run the various testing worlds run the command 
roslaunch mybot_gazebo world1C1.launch 

for the other world run the launch files instead.
world1C1.launch
world1C2.launch
world1C3.launch
world2C1.launch
world2C2.launch
world2C3.launch
world3C1.launch
world3C2.launch
world3C3.launch


Robot model was sourced from https://github.com/richardw05/mybot_ws.git and the accompanying guide (http://moorerobots.com/blog/post/2) not oringal work except for plugin modifications to fit my applications

Dev branch has more advanced code however, it is unstable, ros integration is present there with mcl subscribing to odometry data and camera data. as well, a much more refined file structure specifcly with mcl as it is broken down into idividule files instead of one large one

