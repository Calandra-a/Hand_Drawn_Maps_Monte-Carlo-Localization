// ROS and node class header file
#include <ros/ros.h>
#include "MantisStatePub.h"

int main(int argc, char** argv)
{
  // Initialize ROS and declare node handles
  ros::init(argc, argv, "mantis_state_pub");
  ros::NodeHandle n;
  ros::NodeHandle pn("~");
  
  // Instantiate node class
  mantis_model::MantisStatePub node(n, pn);
  
  // Spin and process callbacks
  ros::spin();
}
