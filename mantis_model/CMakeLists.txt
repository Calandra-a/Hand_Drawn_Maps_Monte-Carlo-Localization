cmake_minimum_required(VERSION 2.8.3)
project(mantis_model)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(mantis_state_pub
  src/mantis_state_pub.cpp
  src/MantisStatePub.cpp
)
target_link_libraries(mantis_state_pub
  ${catkin_LIBRARIES}
)
