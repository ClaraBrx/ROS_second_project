cmake_minimum_required(VERSION 3.0.2)
project(second_project)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  gmapping
  roscpp
  rospy
  tf
  move_base
)

## Declare a catkin package
catkin_package()

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(tf_publisher src/tf_publisher.cpp)
target_link_libraries(tf_publisher ${catkin_LIBRARIES})
add_executable(navigation src/navigation.cpp)
target_link_libraries(navigation ${catkin_LIBRARIES})

