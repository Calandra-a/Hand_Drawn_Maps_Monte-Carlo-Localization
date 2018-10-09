// Header file for the class
#include "MantisStatePub.h"

// Namespace matches ROS package name
namespace mantis_model {

// Constructor with global and private node handle arguments
MantisStatePub::MantisStatePub(ros::NodeHandle n, ros::NodeHandle pn)
{
  pub_joints_ = n.advertise<sensor_msgs::JointState>("/joint_states", 1);
  timer_ = n.createTimer(ros::Duration(0.02), &MantisStatePub::timerCallback, this);
 
  // Set up the structure of the joint state message
  joint_state_msg_.header.frame_id = "base_footprint";  // Root link of the URDF mantis_model
  joint_state_msg_.name.resize(2);                      // Initialize name vector to appropriate size
  joint_state_msg_.position.resize(2, 0);               // Initialize position vector to appropriate size
  
  // Populate name vector with the movable joint names from the URDF model
  joint_state_msg_.name[0] = "left_wheel_joint";
  joint_state_msg_.name[1] = "right_wheel_joint";
}

void MantisStatePub::timerCallback(const ros::TimerEvent& event)
{
  // Constant speed of 1 rad/s
  double speed = 1.0;
  
  // Update time stamp of the joint state message, and increment the angular
  //   position of the wheel joints
  joint_state_msg_.header.stamp = event.current_real;
  joint_state_msg_.position[0] += 0.02 * speed;
  joint_state_msg_.position[1] -= 0.02 * speed;
  
  // Publish the current joint state so the robot_state_publisher can update the TF transforms
  pub_joints_.publish(joint_state_msg_);  
}

  
}
