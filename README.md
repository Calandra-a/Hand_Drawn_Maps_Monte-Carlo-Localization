This Repository is the results of an Undergraduate independent study research project, resulting in a system that will take in hand drawn maps to generate initial map data for a Monte Carlo Localization algorithm

Compiling:
---
navigate to the ResearchProject folder(you'll see a build,devel, and src folder(as well as other files)
and run *catkin_make*

executing
---
you will need to run two commands

first you will launch the gazebo world
---
with the command 

roslaunch mybot_gazebo world1C1.launch 
---
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

Then you will launch the rest of the code:
---

use this command:

rosrun sub_pub topic_publisher_node TestMaterials/fullMap.png TestMaterials/template.png TestMaterials/templateRobot.png
---

These files are provided in the repo, however feel free to create your own. 


Notes: currently the camera sensor isnt subscribed to, I hardcoded the objects it would see into the map to create a testable environment quickly

Also, topic_publisher.cpp is the "main" entry point file currently (not main.cpp, which is actully unused)
In the effort to maintain academic honesty the robot model was sourced from https://github.com/richardw05/mybot_ws.git and the accompanying guide (http://moorerobots.com/blog/post/2) it's not oringal work except for plugin modifications to fit my applications
