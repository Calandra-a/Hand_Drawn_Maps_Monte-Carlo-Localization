cmake_minimum_required(VERSION 2.8.3)

project(sub_pub)

find_package(catkin REQUIRED COMPONENTS 
	roscpp

)

find_package(
	OpenCV
)

catkin_package()

include_directories(
	${catkin_INCLUDE_DIRS}
)

include_directories(
	${OpenCV_INCLUDE_DIRS}
)

add_executable(topic_publisher_node
	topic_publisher.cpp 
)

target_link_libraries(topic_publisher_node
	${catkin_LIBRARIES} 
)

target_link_libraries(topic_publisher_node 
	${OpenCV_LIBRARIES}
)