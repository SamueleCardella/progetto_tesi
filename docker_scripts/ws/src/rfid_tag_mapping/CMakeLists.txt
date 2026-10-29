cmake_minimum_required(VERSION 3.5)
project(rfid_tag_mapping)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(rfid_tag_mapping_node
    src/rfid_tag_mapping_node.cpp
    src/tf_provider.cpp
    src/main.cpp)
    
ament_target_dependencies(rfid_tag_mapping_node 
rclcpp 
std_msgs 
visualization_msgs 
tf2
tf2_ros
geometry_msgs)

include_directories(
  include
)

install(TARGETS
  rfid_tag_mapping_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
