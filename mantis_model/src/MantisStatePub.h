// Include guard to prevent multiple declarations
#ifndef NODECLASS_H
#define NODECLASS_H

// ROS header
#include <ros/ros.h>

#include <sensor_msgs/JointState.h>

// Namespace matches ROS package name
namespace mantis_model{

class MantisStatePub
{
public:
  MantisStatePub(ros::NodeHandle n, ros::NodeHandle pn);
  
private:
  
  void timerCallback(const ros::TimerEvent& event);
  
  ros::Publisher pub_joints_;
  ros::Timer timer_;
  
  sensor_msgs::JointState joint_state_msg_;
};

}

#endif // NODECLASS_H

