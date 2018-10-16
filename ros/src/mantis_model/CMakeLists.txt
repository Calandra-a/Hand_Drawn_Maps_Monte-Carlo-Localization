cmake_minimum_required(VERSION 2.8.3)
project(mantis_model)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(mantis_joint_pub
  src/mantis_joint_pub.cpp src/MantisJointPub.cpp
)
target_link_libraries(mantis_joint_pub
  ${catkin_LIBRARIES}
)
