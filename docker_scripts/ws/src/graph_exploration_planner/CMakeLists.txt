cmake_minimum_required(VERSION 3.5)
project(graph_exploration_planner)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(graph_exploration_planner_node
    src/graph_exploration_planner_node.cpp
    src/map_graph_generator.cpp
    src/main.cpp)
    
ament_target_dependencies(graph_exploration_planner_node 
rclcpp 
nav_msgs
std_msgs 
visualization_msgs 
tf2
tf2_ros
geometry_msgs)

include_directories(
  include
)

install(TARGETS
  graph_exploration_planner_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
